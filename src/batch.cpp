// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::depends(RcppProgress)]]
#include <RcppArmadillo.h>
#include <progress.hpp>

#include <loss.h>
#include <misc.h>
#include <splines.h>
#include <oracle.h>

using namespace arma;

// [[Rcpp::export]]
Rcpp::List batch_rcpp(
    mat &y,
    cube &experts,
    vec tau, // We don't pass by reference here since tau may be modified
    const bool &affine,
    const bool &positive,
    const bool &intercept,
    const bool &debias,
    const int &lead_time,
    const int initial_window,
    const int rolling_window,
    const std::string loss_function,
    const double &loss_parameter,
    const vec &basis_knot_distance,
    const vec &basis_knot_distance_power,
    const vec &basis_deg,
    const vec &forget,
    const vec &soft_threshold,
    const vec &hard_threshold,
    const vec &fixed_share,
    const vec &p_smooth_lambda,
    const vec &p_smooth_knot_distance,
    const vec &p_smooth_knot_distance_power,
    const vec &p_smooth_deg,
    const vec &p_smooth_ndiff,
    const int parametergrid_max_combinations,
    const mat &parametergrid,
    const double &forget_past_performance,
    bool allow_quantile_crossing,
    const bool trace)
{

    if (intercept)
    {
        mat intercept_mat(experts.n_rows, experts.n_cols, fill::ones);
        experts = join_slices(intercept_mat, experts);
    }

    // Indexing Convention -> (T, P, K, X)
    // T number of observations
    // P lengths of probability Grid
    // K number of experts
    // X number of parameter combinations to consider

    // Object Dimensions
    const int T = y.n_rows;
    const int P = experts.n_cols;
    const int K = experts.n_slices;
    const int T_E_Y = experts.n_rows - y.n_rows;

    if (T_E_Y < 0)
        Rcpp::stop("Number of provided expert predictions has to match or exceed observations.");

    if (T <= initial_window)
        Rcpp::stop("Initial estimation window greater or equal to input data.");

    if (y.n_cols > 1 && !allow_quantile_crossing)
    {
        Rcpp::warning("Warning: allow_quantile_crossing set to true since multivariate prediction target was provided.");
        allow_quantile_crossing = true;
    }

    // Expand y matrix if necessary
    if (y.n_cols == 1)
    {
        y = repmat(y, 1, P);
    }

    // Set expand if necessary
    if (tau.n_elem == 1)
    {
        tau.resize(P);
        tau.fill(tau(0));
    }

    if (initial_window > rolling_window)
        Rcpp::stop("Initial estimation window bigger than rolling_window.");

    bool inh_deg = false;
    if (p_smooth_deg.n_elem == 0)
        inh_deg = true;

    bool inh_kstep = false;
    if (p_smooth_knot_distance.n_elem == 0)
        inh_kstep = true;

    bool inh_kstep_p = false;
    if (p_smooth_knot_distance_power.n_elem == 0)
        inh_kstep_p = true;

    // Init parametergrid
    mat param_grid;

    if (parametergrid.n_rows != 0)
    {
        param_grid = parametergrid;
        if (param_grid.n_cols != 12)
            Rcpp::stop("Please provide a parametergrid with 12 columns.");
    }
    else
    {
        // Init parametergrid
        param_grid =
            get_combinations(basis_knot_distance,                                                // Index 0
                             basis_knot_distance_power);                                         // Index 1
        param_grid = get_combinations(param_grid, basis_deg);                                    // index 2
        param_grid = get_combinations(param_grid, forget);                                       // index 3
        param_grid = get_combinations(param_grid, soft_threshold);                               // index 4
        param_grid = get_combinations(param_grid, hard_threshold);                               // index 5
        param_grid = get_combinations(param_grid, fixed_share);                                  // index 6
        param_grid = get_combinations(param_grid, p_smooth_lambda);                              // index 7
        param_grid = get_combinations(param_grid, p_smooth_knot_distance, inh_kstep, 0);         // Index 8
        param_grid = get_combinations(param_grid, p_smooth_knot_distance_power, inh_kstep_p, 1); // Index 9
        param_grid = get_combinations(param_grid, p_smooth_deg, inh_deg, 2);                     // Index 10
        param_grid = get_combinations(param_grid, p_smooth_ndiff);                               // Index 11
    }

    if (param_grid.n_rows > parametergrid_max_combinations)
    {
        Rcpp::warning("Warning: Too many parameter combinations possible. %m combinations were randomly sampled. Results may depend on sampling.", parametergrid_max_combinations);
        uvec tmp_index = randperm(param_grid.n_rows, parametergrid_max_combinations);
        tmp_index = sort(tmp_index);
        param_grid = param_grid.rows(tmp_index);
    }

    const int X = param_grid.n_rows;
    mat chosen_params(T, param_grid.n_cols);
    vec opt_index(T + 1, fill::zeros);
    cube past_performance(T, P, X, fill::zeros);
    vec tmp_performance(X, fill::zeros);
    vec cum_performance(X, fill::zeros);
    Progress prog((T - initial_window) * X + X, trace);

    // Populate uniform weights

    // Init object holding temp. weights, resp. ex-ante
    cube weights_tmp(P, K, X);
    weights_tmp.fill(1 / double(K - intercept * debias));

    if (intercept && debias)
        weights_tmp.col(0).fill(0);

    // Weights output
    cube weights(T + 1, P, K, fill::zeros);

    mat experts_mat(P, K);

    cube predictions_tmp(T, P, X);
    mat predictions_final(T + T_E_Y, P, fill::zeros);

    // Smoothing Setup
    field<mat> hat_mats(param_grid.n_rows);
    vec spline_basis_x = arma::regspace(1, P) / (P + 1);

    // Only if smoothing is possible (tau.size > 1)
    if (P > 1)
    {
        // Init hat matrix field
        for (unsigned int x = 0; x < X; x++)
        {
            // In second step: skip if recalc is not necessary:
            if (x > 0 &&
                param_grid(x, 7) == param_grid(x - 1, 7) &&
                param_grid(x, 8) == param_grid(x - 1, 8) &&
                param_grid(x, 10) == param_grid(x - 1, 10) &&
                param_grid(x, 11) == param_grid(x - 1, 11) &&
                param_grid(x, 9) == param_grid(x - 1, 9))
            {
                hat_mats(x) = hat_mats(x - 1);
            }
            else
            {
                if (param_grid(x, 7) != -datum::inf)
                    hat_mats(x) = make_hat_matrix(spline_basis_x,
                                                  param_grid(x, 8),  // kstep
                                                  param_grid(x, 7),  // lambda
                                                  param_grid(x, 11), // differences
                                                  param_grid(x, 10), // degree
                                                  param_grid(x, 9)   // uneven grid
                    );
            }
            R_CheckUserInterrupt();
            prog.increment(); // Update progress
        }
    }

    field<sp_mat> basis_mats(X);
    field<mat> beta(X);

    // Init hat matrix field
    for (unsigned int x = 0; x < X; x++)
    {

        // In second step: skip if recalc is not necessary:
        if (x > 0 &&
            param_grid(x, 2) == param_grid(x - 1, 2) &&
            param_grid(x, 0) == param_grid(x - 1, 0) &&
            param_grid(x, 1) == param_grid(x - 1, 1))
        {
            basis_mats(x) = basis_mats(x - 1);
        }
        else
        {
            basis_mats(x) = make_basis_matrix(spline_basis_x,
                                              param_grid(x, 0),  // kstep
                                              param_grid(x, 2),  // degree
                                              param_grid(x, 1)); // uneven grid
        }

        beta(x) = (weights_tmp.slice(x).t() * pinv(mat(basis_mats(x))).t()).t();

        R_CheckUserInterrupt();
    }

    // Predictions at t < lead_time + initial_window  using initial weights
    for (unsigned int t = 0; t < initial_window + lead_time; t++)
    {
        // Save final weights weights_tmp
        weights.row(t) = weights_tmp.slice(opt_index(t));

        // Store expert predictions temporarily
        experts_mat = experts.row(t);

        // Forecasters prediction (ex-post)
        mat predictions_temp = sum(weights_tmp.each_slice() % experts_mat, 1);
        predictions_tmp.row(t) = predictions_temp;

        // Final prediction
        predictions_final.row(t) =
            vectorise(predictions_tmp(span(t), span::all, span(opt_index(t)))).t();

        past_performance.row(t).fill(datum::nan);
    }

    // Used for rolling window
    int start = 0;

    for (unsigned int t = (0 + initial_window + lead_time); t < T; t++)
    {
        if (t >= rolling_window)
        {
            start += 1;
        }

        // Save final weights weights_tmp
        weights.row(t) = weights_tmp.slice(opt_index(t));

        // Store expert predictions temporarily
        experts_mat = experts.row(t);

        // Forecasters prediction (ex-post)
        mat predictions_temp = sum(weights_tmp.each_slice() % experts_mat, 1);
        predictions_tmp.row(t) = predictions_temp;

        // Final prediction
        predictions_final.row(t) =
            vectorise(predictions_tmp(span(t), span::all, span(opt_index(t)))).t();

        cube experts_tmp_cube = experts.rows(start, t - lead_time);

        for (unsigned int x = 0; x < X; x++)
        {

            for (unsigned int p = 0; p < P; p++)
            {

                // Evaluate the ex-post predictive performance
                past_performance(t, p, x) = loss(y(t, p),
                                                 predictions_tmp(t - lead_time, p, x),
                                                 9999,           // where evaluate gradient
                                                 loss_function,  // method
                                                 tau(p),         // tau
                                                 loss_parameter, // alpha
                                                 false);

                if (basis_mats(x).is_diagmat())
                {
                    // optim_weights()
                    mat experts_tmp = experts_tmp_cube.col(p);

                    weights_tmp(span(p), span::all, span(x)) = optimize_weights(
                        y(span(start, t - lead_time), p),
                        experts_tmp,
                        affine,
                        positive,
                        intercept,
                        debias,
                        loss_function,
                        tau(p),
                        param_grid(x, 3), // Forget
                        loss_parameter);

                    // Apply thresholds
                    for (double &e : weights_tmp(span(p), span(intercept * debias, K - 1), span(x)))
                    {
                        threshold_soft(e, param_grid(x, 4));
                    }

                    for (double &e : weights_tmp(span(p), span(intercept * debias, K - 1), span(x)))
                    {
                        threshold_hard(e, param_grid(x, 5));
                    }

                    //Add fixed_share
                    weights_tmp(span(p), span(intercept * debias, K - 1), span(x)) *= (1 - param_grid(x, 6));
                    weights_tmp(span(p), span(intercept * debias, K - 1), span(x)) += (param_grid(x, 6) / (K - intercept * debias));
                }
                R_CheckUserInterrupt();
            }

            if (!basis_mats(x).is_diagmat())
            {
                beta(x) = optimize_betas(
                    y.rows(start, t - lead_time),
                    experts_tmp_cube,
                    affine,
                    positive,
                    intercept,
                    debias,
                    loss_function,
                    tau,
                    param_grid(x, 3), // Forget
                    loss_parameter,
                    basis_mats(x),
                    beta(x));

                for (unsigned int l = 0; l < beta(x).n_rows; l++)
                {
                    // Apply thresholds
                    for (double &e : beta(x).row(l))
                    {
                        threshold_soft(e, param_grid(x, 4));
                    }

                    for (double &e : beta(x).row(l))
                    {
                        threshold_hard(e, param_grid(x, 5));
                    }

                    //Add fixed_share
                    beta(x).row(l) =
                        (1 - param_grid(x, 6)) * beta(x).row(l) +
                        (param_grid(x, 6) / K);
                }

                weights_tmp.slice(x) = basis_mats(x) * beta(x);
            }

            // Smoothing
            if (param_grid(x, 7) != -datum::inf)
            {
                weights_tmp.slice(x) = hat_mats(x) * weights_tmp.slice(x);
            }

            // Ensure constraints are met
            for (unsigned int p = 0; p < P; p++)
            {
                if (positive)
                {
                    weights_tmp(span(p), span(intercept * debias, K - 1), span(x)) = pmax_arma(weights_tmp(span(p), span(intercept * debias, K - 1), span(x)), 0);
                }

                if (affine)
                {
                    weights_tmp(span(p), span(intercept * debias, K - 1), span(x)) /= accu(weights_tmp(span(p), span(intercept * debias, K - 1), span(x)));
                }
            }

            tmp_performance(x) = accu(past_performance(span(t), span::all, span(x)));
            prog.increment(); // Update progress
            R_CheckUserInterrupt();
        }

        // Sum past_performance in each slice
        cum_performance = (1 - forget_past_performance) * cum_performance + tmp_performance;
        opt_index(t + 1) = cum_performance.index_min();
        chosen_params.row(t) = param_grid.row(opt_index(t + 1));
    }

    // Save Weights and Prediction
    weights.row(T) = weights_tmp.slice(opt_index(T));

    // Predict residual expert forecasts if any are available
    for (unsigned int t = T; t < T + T_E_Y; t++)
    {
        experts_mat = experts.row(t);
        mat predictions_temp = sum(weights_tmp.slice(opt_index(T)) % experts_mat, 1);
        predictions_final.row(t) = vectorise(predictions_temp).t();
    }

    // Sort predictions if quantile_crossing is prohibited
    if (!allow_quantile_crossing)
    {
        predictions_final = arma::sort(predictions_final, "ascend", 1);
    }

    // Save losses suffered by forecaster and experts
    mat loss_for(T, P, fill::zeros);
    cube loss_exp(T, P, K, fill::zeros);

    for (unsigned int t = 0; t < T; t++)
    {
        for (unsigned int p = 0; p < P; p++)
        {
            for (unsigned int k = 0; k < K; k++)
            {
                loss_exp(t, p, k) =
                    loss(y(t, p),
                         experts(t, p, k),
                         9999,           // where to evaluate the gradient
                         loss_function,  // method
                         tau(p),         // tau
                         loss_parameter, // alpha
                         false);         // gradient
            }
            loss_for(t, p) = loss(y(t, p),
                                  predictions_final(t, p),
                                  9999,           // where to evaluate the gradient
                                  loss_function,  // method
                                  tau(p),         // tau
                                  loss_parameter, // alpha
                                  false);         // gradient;
        }
    }

    // Set unused values to NA
    chosen_params.rows(0, lead_time + initial_window - 1).fill(datum::nan);

    // 1-Indexing for R-Output
    opt_index = opt_index + 1;

    Rcpp::CharacterVector param_names =
        Rcpp::CharacterVector::create("basis_knot_distance",
                                      "basis_knot_distance_power",
                                      "basis_deg",
                                      "forget",
                                      "threshold_soft",
                                      "threshold_hard",
                                      "fixed_share",
                                      "p_smooth_lambda",
                                      "p_smooth_knot_distance",
                                      "p_smooth_knot_distance_power",
                                      "p_smooth_deg",
                                      "smooth_diff");

    Rcpp::NumericMatrix parametergrid_out = Rcpp::wrap(param_grid);
    Rcpp::colnames(parametergrid_out) = param_names;

    Rcpp::NumericMatrix chosen_parameters = Rcpp::wrap(chosen_params);
    Rcpp::colnames(chosen_parameters) = param_names;

    Rcpp::List model_data = Rcpp::List::create(
        Rcpp::Named("y") = y,
        Rcpp::Named("experts") = experts,
        Rcpp::Named("tau") = tau);

    Rcpp::List model_parameters = Rcpp::List::create(
        Rcpp::Named("lead_time") = lead_time,
        Rcpp::Named("loss_function") = loss_function,
        Rcpp::Named("loss_parameter") = loss_parameter,
        Rcpp::Named("forget_past_performance") = forget_past_performance,
        Rcpp::Named("allow_quantile_crossing") = allow_quantile_crossing);

    Rcpp::List model_objects = Rcpp::List::create(
        Rcpp::Named("weights_tmp") = weights_tmp,
        Rcpp::Named("predictions_tmp") = predictions_tmp,
        Rcpp::Named("cum_performance") = cum_performance,
        Rcpp::Named("hat_matrices") = hat_mats,
        Rcpp::Named("beta") = beta);

    Rcpp::List model_spec = Rcpp::List::create(
        Rcpp::Named("data") = model_data,
        Rcpp::Named("parameters") = model_parameters,
        Rcpp::Named("objects") = model_objects);

    Rcpp::List out = Rcpp::List::create(
        Rcpp::Named("predictions") = predictions_final,
        Rcpp::Named("weights") = weights,
        Rcpp::Named("forecaster_loss") = loss_for,
        Rcpp::Named("experts_loss") = loss_exp,
        Rcpp::Named("past_performance") = past_performance,
        Rcpp::Named("chosen_parameters") = chosen_parameters,
        Rcpp::Named("parametergrid") = parametergrid_out,
        Rcpp::Named("opt_index") = opt_index,
        Rcpp::Named("basis_matrices") = basis_mats,
        Rcpp::Named("specification") = model_spec);

    out.attr("class") = "batch";

    return out;
}