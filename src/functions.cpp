// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::depends(RcppProgress)]]
#include <RcppArmadillo.h>
#include <string>
#include <progress.hpp>
using namespace arma;

mat bbase(const vec &x, const int &nseg, const int &deg)
{

  double xl = min(x);
  double xr = max(x);

  double dx = (xr - xl) / nseg;
  int K = round(((xr + deg * dx) - (xl - deg * dx)) / dx + 1);
  vec knots = linspace(xl - deg * dx, xr + deg * dx, K);
  mat P(x.n_rows, knots.n_rows);

  for (unsigned int row_ = 0; row_ < P.n_rows; row_++)
  {
    for (unsigned int col_ = 0; col_ < P.n_cols; col_++)
    {
      P(row_, col_) = pow((x(row_) - knots(col_)), deg) * (x(row_) > knots(col_));
    }
  }

  mat D(knots.n_rows, knots.n_rows, fill::eye);
  D = diff(D, deg + 1);
  D = D / (exp(lgamma(deg + 1)) * pow(dx, deg));
  mat B = pow(-1, deg + 1) * P * D.t();

  return B;
}

mat pmax_arma(const mat &x, const double &bound)
{
  mat out(x);
  for (size_t r = 0; r < x.n_rows; r++)
  {
    for (size_t c = 0; c < x.n_cols; c++)
    {
      if (out(r, c) < bound)
        out(r, c) = bound;
    }
  }
  return out;
}

mat pmin_arma(const mat &x, const double &bound)
{
  mat out(x);
  for (size_t r = 0; r < x.n_rows; r++)
  {
    for (size_t c = 0; c < x.n_cols; c++)
    {
      if (out(r, c) > bound)
        out(r, c) = bound;
    }
  }
  return out;
}

double loss(const double &y,
            const double &x,
            const double &pred = 0,
            const std::string method = "quantile",
            const double &tau = 0.5,
            const double &a = 1,
            const bool &gradient = true)
{
  double loss;

  if (method == "quantile")
  {
    if (!gradient)
    {
      loss = ((y < x) - tau) * (sign(x) * std::pow(std::abs(x), a) - sign(y) * std::pow(std::abs(y), a));
    }
    else
    {
      loss = ((pred >= y) - tau) * (a * std::pow(std::abs(pred), (a - 1)));
      loss = loss * x;
    }
  }
  else if (method == "expectile")
  {
    if (!gradient)
    {

      loss = 2 * std::abs((x >= y) - tau) * (std::pow(std::abs(y), (a + 1)) - std::pow(std::abs(x), (a + 1)) - (a + 1) * sign(x) * std::pow(std::abs(x), a) * (y - x));
    }
    else
    {

      loss = 2 * ((pred >= y) - tau) * (-a * (a + 1) * (y - pred) * std::pow(std::abs(pred), (a - 1)));
      loss = loss * x;
    }
  }
  else if (method == "percentage")
  {
    if (!gradient)
    {
      loss = std::abs(1 - std::pow(x / y, a));
    }
    else
    {
      loss = a * (std::pow(pred / y, a) - 1) * std::pow(pred / y, a) / (pred * std::abs(1 - std::pow(pred / y, a)));
      loss = loss * x;
    }
  }
  else
  {
    Rcpp::stop("Choose quantile loss 'quantile' expectiles 'expectile' or as 'percentage' loss.");
  }
  return loss;
}

mat get_combinations(const mat &x, const vec &y)
{

  int i = 0;

  mat grid(x.n_rows * y.size(), x.n_cols + 1);

  for (unsigned int y_ = 0; y_ < y.size(); y_++)
  {
    for (unsigned int x_ = 0; x_ < x.n_rows; x_++)
    {
      grid(i, span(0, x.n_cols - 1)) = x.row(x_);
      grid(i, x.n_cols) = y(y_);
      i += 1;
    }
  }
  return (grid);
}

vec set_default(const vec &input,
                const double &value)
{
  vec output = input;
  if (output.size() == 0)
  {
    output.set_size(1);
    output(0) = value;
  }

  return output;
}

//' Probabilistic Forecast Combination - ProFoC
//'
//' Returns predictions and weights calculated by online-learning algorithms
//' using CRPS Learning. By default, the weights are calculated by
//' gradient based bernstein online aggregation (BOAG).
//'
//' @param y A numeric vector of realizations.
//' @param experts A an array of predictions with dimension
//' (Observations, Quantiles, Experts).
//' @param tau A numeric vector of probabilities.
//' corresponding to the columns of experts.
//' @param loss_function Either "quantile", "expectile" or "percentage".
//' @param loss_parameter Optional parameter scaling the power of the loss function.
//' @param ex_post_smooth Determines if smoothing is during or after
//' online-learning. If true, contemporary weights are not affected
//' but output weights are. If false (default) smoothed weights are
//' also by the algorithm.
//' @param ex_post_fs Analogous to ex_post_smooth: shall a fixed-share
//' be added during (FALSE) or after online-learning (TRUE).
//' @param lambda Penalization parameter used in the smoothing Step.
//' -Inf causes the smoothing step to be skipped (default).
//' @param method One of "boa", "ml_poly" or "ewa".
//' @param method_var Allows to calculate slight variations of the BOA
//' algorithm
//' @param forget_regret Share of past regret not to be considered, resp. to be
//' forgotten in every iteration of the algorithm. Defaults to 0.
//' @param forget_performance Share of past performance not to be considered, resp. to be
//' forgotten in every iteration of the algorithm when choosing the parameter combination. Defaults to 0.
//' @param fixed_share Amount of fixed share to be added to the weights.
//' Defaults to 0. 1 leads to uniform weights.
//' @param gamma Scaling parameter for the learning rate.
//' @param ndiff Degree of the differencing operator in the smoothing equation. 1 (default) leads to shrikage towards a constant.
//' @param deg Degree of the B-Spine basis functions.
//' @param rel_nseg determines how many basis functions are created in the smoothing step. This parameter defaults to 0.5 leading to 0.5*length(tau) to be used as number of knots. 1 Leads to as many knots as tau is long. 0 leads to one single knot.
//' @param gradient Determines if a linearized version of the loss is used.
//' @param loss_array User specified loss array. If specified, the loss will not be calculated by profoc.
//' @param regret_array User specified regret array. If specifiec, the regret will not be calculated by profoc.
//' @param trace If a progessbar shall be printed. Defaults to TRUE.
//' @param init_weights Matrix of dimension Kx1 or KxP used as starting weights. Kx1 represents the constant solution with equal weights over all P whereas specifiying a KxP matrix allows different starting weights for each P.
//' @param lead_time offset for expert forecasts. Defaults to 0, which means that
//' experts forecast t+1 at t. Setting this to h means experts predictions refer
//' to t+1+h at time t. The weight updates delay accordingly.
//' @usage profoc(y, experts, tau, loss_function = "quantile",
//' loss_parameter = 1, ex_post_smooth = FALSE, ex_post_fs = FALSE,
//' lambda = -Inf, method = "boa", method_var = "A", forget_regret = 0,
//' forget_performance = 0, fixed_share = 0, gamma = 1, ndiff = 1, deg = 3,
//'rel_nseg = 0.5, gradient = TRUE, loss_array = NULL, regret_array = NULL,
//' trace = TRUE, init_weights = NULL, lead_time = 0)
//' @return Profoc can tune various parameters automatically based on
//' the past loss. For this, lambda, forget, fixed_share, gamma, ndiff,
//' deg and rel_nseg can be specified as numeric vectors containing
//' parameters to consider. Profoc will automatically try all possible
//' combinations of values provide.
//' @export
// [[Rcpp::export]]
Rcpp::List profoc(
    mat &y,
    const cube &experts,
    Rcpp::NumericVector tau = Rcpp::NumericVector::create(),
    const std::string loss_function = "quantile",
    const double &loss_parameter = 1,
    const bool &ex_post_smooth = false,
    const bool &ex_post_fs = false,
    Rcpp::NumericVector lambda = Rcpp::NumericVector::create(),
    const std::string method = "boa",
    const std::string method_var = "A",
    Rcpp::NumericVector forget_regret = Rcpp::NumericVector::create(),
    const double &forget_performance = 0,
    Rcpp::NumericVector fixed_share = Rcpp::NumericVector::create(),
    Rcpp::NumericVector gamma = Rcpp::NumericVector::create(),
    Rcpp::NumericVector ndiff = Rcpp::NumericVector::create(),
    Rcpp::NumericVector deg = Rcpp::NumericVector::create(),
    Rcpp::NumericVector rel_nseg = Rcpp::NumericVector::create(),
    const bool &gradient = true,
    Rcpp::NumericVector loss_array = Rcpp::NumericVector::create(),
    Rcpp::NumericVector regret_array = Rcpp::NumericVector::create(),
    const bool trace = true,
    Rcpp::Nullable<Rcpp::NumericMatrix> init_weights = R_NilValue,
    const int &lead_time = 0)
{
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

  // Expand y matrix if necessary
  if (y.n_cols == 1)
  {
    y = repmat(y, 1, P);
  }

  // Set default value to tau and / or expand if necessary
  vec tau_vec(tau);
  if (tau_vec.size() == 0)
  {
    tau_vec.resize(P);
    tau_vec = regspace(1, P) / (P + 1);
  }
  else if (tau_vec.size() == 1)
  {
    tau_vec.resize(P);
    tau_vec.fill(tau_vec(0));
  }

  // Set default values
  vec lambda_vec = set_default(lambda, -datum::inf);
  vec forget_vec = set_default(forget_regret, 0);
  vec fixed_share_vec = set_default(fixed_share, 0);
  vec gamma_vec = set_default(gamma, 1);
  vec rel_nseg_vec = set_default(rel_nseg, 0.5);
  vec deg_vec = set_default(deg, 3);
  vec diff_vec = set_default(ndiff, 1);

  // Init parametergrid
  mat param_grid = get_combinations(lambda_vec, forget_vec);
  param_grid = get_combinations(param_grid, fixed_share_vec);
  param_grid = get_combinations(param_grid, gamma_vec);
  param_grid = get_combinations(param_grid, rel_nseg_vec);
  param_grid = get_combinations(param_grid, deg_vec);
  param_grid = get_combinations(param_grid, diff_vec);

  const int X = param_grid.n_rows;
  mat chosen_params(T, param_grid.n_cols);
  vec opt_index(T + 1, fill::zeros);
  cube past_performance(T, P, X, fill::zeros);
  vec tmp_performance(X, fill::zeros);
  vec cum_performance(X, fill::zeros);
  Progress prog(T * X + X, trace);

  // Init weight objects

  mat w0;
  // Populate uniform weights if w0 was not specified
  if (init_weights.isNotNull())
  {
    w0 = Rcpp::as<arma::mat>(init_weights);
  }
  else
  {
    w0.resize(K);
    w0.fill(1 / double(K));
  }

  // Expand w0 if necessary
  if (w0.n_cols == 1)
  {
    w0 = repmat(w0, 1, P);
  }

  // Truncate from below
  w0 = pmax_arma(w0, exp(-350));

  // Normalize weights
  w0 = w0.each_row() / sum(w0);

  // Init object holding temp. weights, resp. ex-ante
  cube w_temp(P, K, X);
  w_temp.each_slice() = w0.t();
  // Init object holding final weights, resp. ex-post
  cube w_post(w_temp);

  // Weights output
  cube weights(T + 1, P, K, fill::zeros);

  cube R(P, K, X, fill::zeros);
  cube R_reg(R);
  cube eta(P, K, X, fill::zeros);
  if (method == "ml_poly")
    eta.fill(exp(350));
  cube V(P, K, X, fill::zeros);
  cube E(P, K, X, fill::zeros);
  cube k(P, K, X, fill::zeros);
  k = k.fill(-699);
  mat experts_mat(P, K);

  cube predictions_post(T, P, X);
  cube predictions_ante(T, P, X);
  mat predictions_temp(P, K);
  mat predictions_final(T + T_E_Y, P);

  vec lpred(1);
  vec lexp(K);
  vec r(K);
  vec r_reg(K);
  cube loss_cube(T, P, K, fill::zeros);

  // Init loss array (if existent)
  if (loss_array.size() > 0)
  {
    vec dim = loss_array.attr("dim");
    cube tmp_cube(loss_array.begin(), dim(0), dim(1), dim(2), false);
    loss_cube = tmp_cube;
  }

  cube regret_cube(T, P, K, fill::zeros);
  // Init regret array (if existent)
  if (regret_array.size() > 0)
  {
    vec dim = regret_array.attr("dim");
    cube tmp_cube(regret_array.begin(), dim(0), dim(1), dim(2), false);
    regret_cube = tmp_cube;
  }

  // Smoothing Setup
  field<mat> hat_mats(param_grid.n_rows);
  vec spline_basis_x = regspace(1, P) / (P + 1);

  // Only if smoothing is possible (tau_vec.size > 1)
  if (P > 1)
  {

    // Init hat matrix field
    for (unsigned int x = 0; x < X; x++)
    {
      // In second step: skip if recalc is not necessary:
      if (x > 0 &&
          param_grid(x, 0) == param_grid(x - 1, 0) &&
          param_grid(x, 4) == param_grid(x - 1, 4) &&
          param_grid(x, 5) == param_grid(x - 1, 5) &&
          param_grid(x, 6) == param_grid(x - 1, 6))
      {
        hat_mats(x) = hat_mats(x - 1);
      }
      else
      {
        // Number of segments
        int nseg = std::min(std::max(double(1), ceil(P * param_grid(x, 4))), double(P));

        // Create bspline basis
        mat B = bbase(spline_basis_x, nseg, param_grid(x, 5));

        // Create roughness measure
        mat D(B.n_cols, B.n_cols, fill::eye);
        D = diff(D, param_grid(x, 6));

        hat_mats(x) = B * inv(B.t() * B + param_grid(x, 0) * D.t() * D) * B.t();
      }
      R_CheckUserInterrupt();
      prog.increment(); // Update progress
    }
  }

  // Predictions at t < lead_time using initial weights
  for (unsigned int t = 0; t < lead_time; t++)
  {
    // Save final weights w_post
    weights.row(t) = w_post.slice(opt_index(t));

    // Store expert predictions temporarily
    experts_mat = experts.row(t);

    // Forecasters prediction(ex-ante)
    predictions_temp = sum(w_temp.each_slice() % experts_mat, 1);
    predictions_ante.row(t) = predictions_temp;

    // Forecasters prediction (ex-post)
    // Note that w_post != w_temp in ex post setting and w_post = w_temp otherwise
    predictions_temp = sum(w_post.each_slice() % experts_mat, 1);
    predictions_post.row(t) = predictions_temp;

    // Final prediction
    predictions_final.row(t) =
        vectorise(predictions_post(span(t), span::all, span(opt_index(t)))).t();

    past_performance.row(t).fill(datum::nan);
  }

  for (unsigned int t = (0 + lead_time); t < T; t++)
  {

    // Save final weights w_post
    weights.row(t) = w_post.slice(opt_index(t));

    // Store expert predictions temporarily
    experts_mat = experts.row(t);

    // Forecasters prediction(ex-ante)
    predictions_temp = sum(w_temp.each_slice() % experts_mat, 1);
    predictions_ante.row(t) = predictions_temp;

    // Forecasters prediction (ex-post)
    // Note that w_post != w_temp in ex post setting and w_post = w_temp otherwise
    predictions_temp = sum(w_post.each_slice() % experts_mat, 1);
    predictions_post.row(t) = predictions_temp;

    // Final prediction
    predictions_final.row(t) =
        vectorise(predictions_post(span(t), span::all, span(opt_index(t)))).t();

    for (unsigned int x = 0; x < X; x++)
    {
      for (unsigned int p = 0; p < P; p++)
      {

        // Evaluate the ex-post predictive performance
        past_performance(t, p, x) = loss(y(t, p),
                                         predictions_post(t - lead_time, p, x),
                                         9999,           // where evaluate gradient
                                         loss_function,  // method
                                         tau_vec(p),     // tau_vec
                                         loss_parameter, // alpha
                                         false);

        for (unsigned int k = 0; k < K; k++)
        {
          lexp(k) = loss(y(t, p),
                         experts(t, p, k),
                         predictions_ante(t - lead_time, p, x), // where evaluate gradient
                         loss_function,                         // method
                         tau_vec(p),                            // tau_vec
                         loss_parameter,                        // alpha
                         gradient);
        }

        lpred = loss(y(t, p),
                     predictions_ante(t - lead_time, p, x),
                     predictions_ante(t - lead_time, p, x), // where to evaluate gradient
                     loss_function,                         // method
                     tau_vec(p),                            // tau_vec
                     loss_parameter,                        // alpha
                     gradient);

        if (loss_array.size() != 0)
        {
          lexp = loss_cube(span(t), span(p), span::all);
        }

        if (regret_array.size() == 0)
        {
          r = lpred - lexp.each_row();
        }
        else
        {
          r = regret_cube(span(t), span(p), span::all);
        }

        if (method == "ewa")
        {
          // Update the cumulative regret used by eta
          R(span(p), span::all, span(x)) = vectorise(R(span(p), span::all, span(x))) * (1 - param_grid(x, 1)) + r;
          w_temp(span(p), span::all, span(x)) = exp(param_grid(x, 3) * vectorise(R(span(p), span::all, span(x))));
          w_temp(span(p), span::all, span(x)) = w_temp(span(p), span::all, span(x)) / accu(w_temp(span(p), span::all, span(x)));
        }
        else if (method == "ml_poly")
        {
          // Update the cumulative regret used by ML_Poly
          R(span(p), span::all, span(x)) = vectorise(R(span(p), span::all, span(x))) * (1 - param_grid(x, 1)) + r;

          // Update the learning rate
          eta(span(p), span::all, span(x)) = 1 / (1 / vectorise(eta(span(p), span::all, span(x))) + square(r));

          // param_grid(x, 3) = gamma
          w_temp(span(p), span::all, span(x)) = param_grid(x, 3) * vectorise(eta(span(p), span::all, span(x))) % pmax_arma(R(span(p), span::all, span(x)), exp(-700)).t();
          w_temp(span(p), span::all, span(x)) = w_temp(span(p), span::all, span(x)) / accu(w_temp(span(p), span::all, span(x)));
        }
        else if (method == "boa")
        {

          V(span(p), span::all, span(x)) = vectorise(V(span(p), span::all, span(x))) * (1 - param_grid(x, 1)) + square(r);

          // Update the bounds and learning rates
          E(span(p), span::all, span(x)) = max(vectorise(E(span(p), span::all, span(x))) * (1 - param_grid(x, 1)), abs(r));

          eta(span(p), span::all, span(x)) =
              pmin_arma(
                  min(1 / (2 * vectorise(E(span(p), span::all, span(x)))),
                      sqrt(log(K) / vectorise(V(span(p), span::all, span(x))))),
                  exp(350));

          // Instantaneous regularized regret
          r_reg = r - vectorise(eta(span(p), span::all, span(x))) % square(r);

          // Update cumulative regularized regret
          if (method_var.find('A') != std::string::npos)
          {
            R_reg(span(p), span::all, span(x)) = vectorise(R_reg(span(p), span::all, span(x))) * (1 - param_grid(x, 1)) + 0.5 * (r_reg + conv_to<colvec>::from(vectorise(eta(span(p), span::all, span(x))) % r > 0.5) % (2 * vectorise(E(span(p), span::all, span(x)))));
          }
          else
          {
            // Gaillard
            R_reg(span(p), span::all, span(x)) = vectorise(R_reg(span(p), span::all, span(x))) * (1 - param_grid(x, 1)) + r_reg;
          }

          // Update weights and truncate if necessary
          if (method_var.find('C') != std::string::npos)
          {
            // Wintenberger
            w_temp(span(p), span::all, span(x)) = param_grid(x, 3) * vectorise(eta(span(p), span::all, span(x))) % exp(param_grid(x, 3) * vectorise(eta(span(p), span::all, span(x))) % vectorise(R_reg(span(p), span::all, span(x)))) % w0.col(p);
            w_temp(span(p), span::all, span(x)) = w_temp(span(p), span::all, span(x)) / mean(param_grid(x, 3) * vectorise(eta(span(p), span::all, span(x))) % exp(param_grid(x, 3) * vectorise(eta(span(p), span::all, span(x))) % vectorise(R_reg(span(p), span::all, span(x)))));
          }
          else
          {
            // Gaillard
            w_temp(span(p), span::all, span(x)) = exp(param_grid(x, 3) * vectorise(eta(span(p), span::all, span(x))) % vectorise(R_reg(span(p), span::all, span(x))));
            w_temp(span(p), span::all, span(x)) = pmin_arma(pmax_arma(w_temp(span(p), span::all, span(x)), exp(-700)), exp(700));
            w_temp(span(p), span::all, span(x)) = w_temp(span(p), span::all, span(x)) / accu(w_temp(span(p), span::all, span(x)));
          }
        }
        else
        {
          Rcpp::stop("Choose 'boa', 'ml_poly' or 'ewa' as method.");
        }
      }

      w_post.slice(x) = w_temp.slice(x);

      // Smoothing Step
      if (param_grid(x, 0) != -datum::inf)
      {
        for (unsigned int k = 0; k < K; k++)
        {
          if (!ex_post_smooth)
          {
            w_temp(span::all, span(k), span(x)) = hat_mats(x) * vectorise(w_temp(span::all, span(k), span(x)));
            // Truncate to zero
            w_temp(span::all, span(k), span(x)) = pmax_arma(w_temp(span::all, span(k), span(x)), exp(-700));
            w_post(span::all, span(k), span(x)) = w_temp(span::all, span(k), span(x));
          }
          else
          {
            w_post(span::all, span(k), span(x)) = hat_mats(x) * vectorise(w_temp(span::all, span(k), span(x)));
            w_post(span::all, span(k), span(x)) = pmax_arma(w_post(span::all, span(k), span(x)), exp(-700));
          }
        }
      }

      //Add fixed_share
      for (unsigned int p = 0; p < P; p++)
      {
        if (ex_post_fs) // Fixed share only added to w_post
        {
          w_post(span(p), span::all, span(x)) = (1 - param_grid(x, 2)) * (w_post(span(p), span::all, span(x)) / accu(w_post(span(p), span::all, span(x)))) + (param_grid(x, 2) / K);
        }
        else if (ex_post_smooth && !ex_post_fs)
        {
          // Add fixed_share to wtemp
          w_post(span(p), span::all, span(x)) = (1 - param_grid(x, 2)) * (w_post(span(p), span::all, span(x)) / accu(w_post(span(p), span::all, span(x)))) + (param_grid(x, 2) / K);
          // Add fixed_share to w_temp
          w_temp(span(p), span::all, span(x)) = (1 - param_grid(x, 2)) * (w_temp(span(p), span::all, span(x)) / accu(w_temp(span(p), span::all, span(x)))) + (param_grid(x, 2) / K);
        }
        else if (!ex_post_smooth && !ex_post_fs)
        {
          w_temp(span(p), span::all, span(x)) = (1 - param_grid(x, 2)) * (w_temp(span(p), span::all, span(x)) / accu(w_temp(span(p), span::all, span(x)))) + (param_grid(x, 2) / K);
          w_post(span(p), span::all, span(x)) = w_temp(span(p), span::all, span(x));
        }
      }
      tmp_performance(x) = accu(past_performance(span(t), span::all, span(x)));
      prog.increment(); // Update progress
      R_CheckUserInterrupt();
    }

    // Sum past_performance in each slice
    cum_performance = (1 - forget_performance) * cum_performance + tmp_performance;
    opt_index(t + 1) = cum_performance.index_min();
    chosen_params.row(t) = param_grid.row(opt_index(t + 1));
  }

  // Save Weights and Prediction
  weights.row(T) = w_post.slice(opt_index(T));

  // Predict residual expert forecasts if any are available
  for (unsigned int t = T; t < T + T_E_Y; t++)
  {
    experts_mat = experts.row(t);
    predictions_temp = sum(w_post.slice(opt_index(T)) % experts_mat, 1);
    predictions_final.row(t) = vectorise(predictions_temp).t();
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
                 tau_vec(p),     // tau_vec
                 loss_parameter, // alpha
                 false);         // gradient
      }
      loss_for(t, p) = loss(y(t, p),
                            predictions_final(t, p),
                            9999,           // where to evaluate the gradient
                            loss_function,  // method
                            tau_vec(p),     // tau_vec
                            loss_parameter, // alpha
                            false);         // gradient;
    }
  }

  // 1-Indexing for R-Output
  opt_index = opt_index + 1;

  Rcpp::DataFrame opt_params_df = Rcpp::DataFrame::create(
      Rcpp::Named("lambda") = chosen_params.col(0),
      Rcpp::Named("forget_regret") = chosen_params.col(1),
      Rcpp::Named("fixed_share") = chosen_params.col(2),
      Rcpp::Named("gamma") = chosen_params.col(3),
      Rcpp::Named("rel_nseg") = chosen_params.col(4),
      Rcpp::Named("deg") = chosen_params.col(5),
      Rcpp::Named("diff") = chosen_params.col(6));
  ;

  Rcpp::DataFrame parametergrid = Rcpp::DataFrame::create(
      Rcpp::Named("lambda") = param_grid.col(0),
      Rcpp::Named("forget_regret") = param_grid.col(1),
      Rcpp::Named("fixed_share") = param_grid.col(2),
      Rcpp::Named("gamma") = param_grid.col(3),
      Rcpp::Named("rel_nseg") = param_grid.col(4),
      Rcpp::Named("deg") = param_grid.col(5),
      Rcpp::Named("diff") = param_grid.col(6));
  ;

  return Rcpp::List::create(
      Rcpp::Named("predictions") = predictions_final,
      Rcpp::Named("weights") = weights,
      Rcpp::Named("forecaster_loss") = loss_for,
      Rcpp::Named("experts_loss") = loss_exp,
      Rcpp::Named("past_perf_wrt_params") = past_performance,
      Rcpp::Named("chosen_parameters") = opt_params_df,
      Rcpp::Named("parametergrid") = parametergrid,
      Rcpp::Named("opt_index") = opt_index);
}

//' Spline Fit - Fit Penalized B-Splines
//'
//' Returns fitted values.
//'
//' @param y The respones variable. Must be a numeric vector.
//' @param x Explanatory variable. Must be a numeric vector.
//' @param lambda The penalization parameter.
//' @param ndiff Degree of the difference operator to use when calculating
//' the B-Spline basis. A value of 1 corresponds to shrinkage towards
//' a constant, 2 corresponds to shrinkage towards a linear relationship
//' between x and y.
//' @param deg the degree of the basis functions.
//' @param rel_nseg The number of basis functions are calculated relative to the
//' length of y. A value of 0 corresponds to only 1 knot. A value of 1
//' corresponds to length(y) knots.
//' @export
// [[Rcpp::export]]
vec spline_fit(const vec &y, const vec &x, const double &lambda = 1, const int &ndiff = 1, const int &deg = 3, const double &rel_nseg = 0.1)
{

  // Number of segments
  int nseg = std::max(double(1), ceil(y.n_rows * rel_nseg));

  // Create bspline basis
  mat B = bbase(x, nseg, deg);

  // Create roughness measure
  mat D(B.n_cols, B.n_cols, fill::eye);
  D = diff(D, ndiff);

  // Calculate fitted values
  vec y_hat = B * inv(B.t() * B + lambda * D.t() * D) * B.t() * y;

  return y_hat;
}