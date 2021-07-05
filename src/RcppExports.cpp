// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "../inst/include/profoc.h"
#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// batch
Rcpp::List batch(mat& y, cube& experts, Rcpp::NumericVector tau, const bool& affine, const bool& positive, const bool& intercept, const bool& debias, const int& lead_time, int initial_window, const bool expanding_window, const std::string loss_function, const double& loss_parameter, Rcpp::NumericVector basis_knot_distance, Rcpp::NumericVector basis_knot_distance_power, Rcpp::NumericVector basis_deg, Rcpp::NumericVector forget, Rcpp::NumericVector soft_threshold, Rcpp::NumericVector hard_threshold, Rcpp::NumericVector fixed_share, Rcpp::NumericVector smooth_lambda, Rcpp::NumericVector smooth_knot_distance, Rcpp::NumericVector smooth_knot_distance_power, Rcpp::NumericVector smooth_deg, Rcpp::NumericVector smooth_ndiff, const int parametergrid_max_combinations, const double& forget_past_performance, bool allow_quantile_crossing, const bool trace);
RcppExport SEXP _profoc_batch(SEXP ySEXP, SEXP expertsSEXP, SEXP tauSEXP, SEXP affineSEXP, SEXP positiveSEXP, SEXP interceptSEXP, SEXP debiasSEXP, SEXP lead_timeSEXP, SEXP initial_windowSEXP, SEXP expanding_windowSEXP, SEXP loss_functionSEXP, SEXP loss_parameterSEXP, SEXP basis_knot_distanceSEXP, SEXP basis_knot_distance_powerSEXP, SEXP basis_degSEXP, SEXP forgetSEXP, SEXP soft_thresholdSEXP, SEXP hard_thresholdSEXP, SEXP fixed_shareSEXP, SEXP smooth_lambdaSEXP, SEXP smooth_knot_distanceSEXP, SEXP smooth_knot_distance_powerSEXP, SEXP smooth_degSEXP, SEXP smooth_ndiffSEXP, SEXP parametergrid_max_combinationsSEXP, SEXP forget_past_performanceSEXP, SEXP allow_quantile_crossingSEXP, SEXP traceSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< mat& >::type y(ySEXP);
    Rcpp::traits::input_parameter< cube& >::type experts(expertsSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type tau(tauSEXP);
    Rcpp::traits::input_parameter< const bool& >::type affine(affineSEXP);
    Rcpp::traits::input_parameter< const bool& >::type positive(positiveSEXP);
    Rcpp::traits::input_parameter< const bool& >::type intercept(interceptSEXP);
    Rcpp::traits::input_parameter< const bool& >::type debias(debiasSEXP);
    Rcpp::traits::input_parameter< const int& >::type lead_time(lead_timeSEXP);
    Rcpp::traits::input_parameter< int >::type initial_window(initial_windowSEXP);
    Rcpp::traits::input_parameter< const bool >::type expanding_window(expanding_windowSEXP);
    Rcpp::traits::input_parameter< const std::string >::type loss_function(loss_functionSEXP);
    Rcpp::traits::input_parameter< const double& >::type loss_parameter(loss_parameterSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type basis_knot_distance(basis_knot_distanceSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type basis_knot_distance_power(basis_knot_distance_powerSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type basis_deg(basis_degSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type forget(forgetSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type soft_threshold(soft_thresholdSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type hard_threshold(hard_thresholdSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type fixed_share(fixed_shareSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type smooth_lambda(smooth_lambdaSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type smooth_knot_distance(smooth_knot_distanceSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type smooth_knot_distance_power(smooth_knot_distance_powerSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type smooth_deg(smooth_degSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type smooth_ndiff(smooth_ndiffSEXP);
    Rcpp::traits::input_parameter< const int >::type parametergrid_max_combinations(parametergrid_max_combinationsSEXP);
    Rcpp::traits::input_parameter< const double& >::type forget_past_performance(forget_past_performanceSEXP);
    Rcpp::traits::input_parameter< bool >::type allow_quantile_crossing(allow_quantile_crossingSEXP);
    Rcpp::traits::input_parameter< const bool >::type trace(traceSEXP);
    rcpp_result_gen = Rcpp::wrap(batch(y, experts, tau, affine, positive, intercept, debias, lead_time, initial_window, expanding_window, loss_function, loss_parameter, basis_knot_distance, basis_knot_distance_power, basis_deg, forget, soft_threshold, hard_threshold, fixed_share, smooth_lambda, smooth_knot_distance, smooth_knot_distance_power, smooth_deg, smooth_ndiff, parametergrid_max_combinations, forget_past_performance, allow_quantile_crossing, trace));
    return rcpp_result_gen;
END_RCPP
}
// loss
double loss(const double& y, const double& x, const double& pred, const std::string method, const double& tau, const double& a, const bool& gradient);
RcppExport SEXP _profoc_loss(SEXP ySEXP, SEXP xSEXP, SEXP predSEXP, SEXP methodSEXP, SEXP tauSEXP, SEXP aSEXP, SEXP gradientSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const double& >::type y(ySEXP);
    Rcpp::traits::input_parameter< const double& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const double& >::type pred(predSEXP);
    Rcpp::traits::input_parameter< const std::string >::type method(methodSEXP);
    Rcpp::traits::input_parameter< const double& >::type tau(tauSEXP);
    Rcpp::traits::input_parameter< const double& >::type a(aSEXP);
    Rcpp::traits::input_parameter< const bool& >::type gradient(gradientSEXP);
    rcpp_result_gen = Rcpp::wrap(loss(y, x, pred, method, tau, a, gradient));
    return rcpp_result_gen;
END_RCPP
}
// loss_grad_wrt_w
double loss_grad_wrt_w(const double& expert, const double& pred, const double& truth, const double& tau, const std::string& loss_function, const double& a, const double& w);
RcppExport SEXP _profoc_loss_grad_wrt_w(SEXP expertSEXP, SEXP predSEXP, SEXP truthSEXP, SEXP tauSEXP, SEXP loss_functionSEXP, SEXP aSEXP, SEXP wSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const double& >::type expert(expertSEXP);
    Rcpp::traits::input_parameter< const double& >::type pred(predSEXP);
    Rcpp::traits::input_parameter< const double& >::type truth(truthSEXP);
    Rcpp::traits::input_parameter< const double& >::type tau(tauSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type loss_function(loss_functionSEXP);
    Rcpp::traits::input_parameter< const double& >::type a(aSEXP);
    Rcpp::traits::input_parameter< const double& >::type w(wSEXP);
    rcpp_result_gen = Rcpp::wrap(loss_grad_wrt_w(expert, pred, truth, tau, loss_function, a, w));
    return rcpp_result_gen;
END_RCPP
}
// pmin_arma
mat pmin_arma(const mat& x, const double& bound);
RcppExport SEXP _profoc_pmin_arma(SEXP xSEXP, SEXP boundSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const mat& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const double& >::type bound(boundSEXP);
    rcpp_result_gen = Rcpp::wrap(pmin_arma(x, bound));
    return rcpp_result_gen;
END_RCPP
}
// pmax_arma
mat pmax_arma(const mat& x, const double& bound);
RcppExport SEXP _profoc_pmax_arma(SEXP xSEXP, SEXP boundSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const mat& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const double& >::type bound(boundSEXP);
    rcpp_result_gen = Rcpp::wrap(pmax_arma(x, bound));
    return rcpp_result_gen;
END_RCPP
}
// diff_cpp
vec diff_cpp(vec x, unsigned int lag, unsigned int differences);
RcppExport SEXP _profoc_diff_cpp(SEXP xSEXP, SEXP lagSEXP, SEXP differencesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< vec >::type x(xSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type lag(lagSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type differences(differencesSEXP);
    rcpp_result_gen = Rcpp::wrap(diff_cpp(x, lag, differences));
    return rcpp_result_gen;
END_RCPP
}
// get_combinations
mat get_combinations(const mat& x, const vec& y, const bool& append_only, const int& append_col);
RcppExport SEXP _profoc_get_combinations(SEXP xSEXP, SEXP ySEXP, SEXP append_onlySEXP, SEXP append_colSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const mat& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const vec& >::type y(ySEXP);
    Rcpp::traits::input_parameter< const bool& >::type append_only(append_onlySEXP);
    Rcpp::traits::input_parameter< const int& >::type append_col(append_colSEXP);
    rcpp_result_gen = Rcpp::wrap(get_combinations(x, y, append_only, append_col));
    return rcpp_result_gen;
END_RCPP
}
// set_default
vec set_default(const vec& input, const double& value);
RcppExport SEXP _profoc_set_default(SEXP inputSEXP, SEXP valueSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const vec& >::type input(inputSEXP);
    Rcpp::traits::input_parameter< const double& >::type value(valueSEXP);
    rcpp_result_gen = Rcpp::wrap(set_default(input, value));
    return rcpp_result_gen;
END_RCPP
}
// vec2mat
mat vec2mat(const vec& x, const int& matrows, const int& matcols);
RcppExport SEXP _profoc_vec2mat(SEXP xSEXP, SEXP matrowsSEXP, SEXP matcolsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const vec& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const int& >::type matrows(matrowsSEXP);
    Rcpp::traits::input_parameter< const int& >::type matcols(matcolsSEXP);
    rcpp_result_gen = Rcpp::wrap(vec2mat(x, matrows, matcols));
    return rcpp_result_gen;
END_RCPP
}
// mat2vec
vec mat2vec(const mat& x);
RcppExport SEXP _profoc_mat2vec(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const mat& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(mat2vec(x));
    return rcpp_result_gen;
END_RCPP
}
// online
Rcpp::List online(mat& y, cube& experts, Rcpp::NumericVector tau, const int& lead_time, const std::string loss_function, const double& loss_parameter, const bool& loss_gradient, const std::string method, const std::string method_var, Rcpp::NumericVector basis_knot_distance, Rcpp::NumericVector basis_knot_distance_power, Rcpp::NumericVector basis_deg, Rcpp::NumericVector forget_regret, Rcpp::NumericVector soft_threshold, bool soft_threshold_ex_post, Rcpp::NumericVector hard_threshold, bool hard_threshold_ex_post, Rcpp::NumericVector fixed_share, const bool& fixed_share_ex_post, Rcpp::NumericVector smooth_lambda, Rcpp::NumericVector smooth_knot_distance, Rcpp::NumericVector smooth_knot_distance_power, Rcpp::NumericVector smooth_deg, Rcpp::NumericVector smooth_ndiff, const bool& smooth_ex_post, Rcpp::NumericVector gamma, const int parametergrid_max_combinations, const double& forget_past_performance, bool allow_quantile_crossing, Rcpp::Nullable<Rcpp::NumericMatrix> init_weights, Rcpp::NumericVector loss_array, Rcpp::NumericVector regret_array, const bool trace);
RcppExport SEXP _profoc_online(SEXP ySEXP, SEXP expertsSEXP, SEXP tauSEXP, SEXP lead_timeSEXP, SEXP loss_functionSEXP, SEXP loss_parameterSEXP, SEXP loss_gradientSEXP, SEXP methodSEXP, SEXP method_varSEXP, SEXP basis_knot_distanceSEXP, SEXP basis_knot_distance_powerSEXP, SEXP basis_degSEXP, SEXP forget_regretSEXP, SEXP soft_thresholdSEXP, SEXP soft_threshold_ex_postSEXP, SEXP hard_thresholdSEXP, SEXP hard_threshold_ex_postSEXP, SEXP fixed_shareSEXP, SEXP fixed_share_ex_postSEXP, SEXP smooth_lambdaSEXP, SEXP smooth_knot_distanceSEXP, SEXP smooth_knot_distance_powerSEXP, SEXP smooth_degSEXP, SEXP smooth_ndiffSEXP, SEXP smooth_ex_postSEXP, SEXP gammaSEXP, SEXP parametergrid_max_combinationsSEXP, SEXP forget_past_performanceSEXP, SEXP allow_quantile_crossingSEXP, SEXP init_weightsSEXP, SEXP loss_arraySEXP, SEXP regret_arraySEXP, SEXP traceSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< mat& >::type y(ySEXP);
    Rcpp::traits::input_parameter< cube& >::type experts(expertsSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type tau(tauSEXP);
    Rcpp::traits::input_parameter< const int& >::type lead_time(lead_timeSEXP);
    Rcpp::traits::input_parameter< const std::string >::type loss_function(loss_functionSEXP);
    Rcpp::traits::input_parameter< const double& >::type loss_parameter(loss_parameterSEXP);
    Rcpp::traits::input_parameter< const bool& >::type loss_gradient(loss_gradientSEXP);
    Rcpp::traits::input_parameter< const std::string >::type method(methodSEXP);
    Rcpp::traits::input_parameter< const std::string >::type method_var(method_varSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type basis_knot_distance(basis_knot_distanceSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type basis_knot_distance_power(basis_knot_distance_powerSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type basis_deg(basis_degSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type forget_regret(forget_regretSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type soft_threshold(soft_thresholdSEXP);
    Rcpp::traits::input_parameter< bool >::type soft_threshold_ex_post(soft_threshold_ex_postSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type hard_threshold(hard_thresholdSEXP);
    Rcpp::traits::input_parameter< bool >::type hard_threshold_ex_post(hard_threshold_ex_postSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type fixed_share(fixed_shareSEXP);
    Rcpp::traits::input_parameter< const bool& >::type fixed_share_ex_post(fixed_share_ex_postSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type smooth_lambda(smooth_lambdaSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type smooth_knot_distance(smooth_knot_distanceSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type smooth_knot_distance_power(smooth_knot_distance_powerSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type smooth_deg(smooth_degSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type smooth_ndiff(smooth_ndiffSEXP);
    Rcpp::traits::input_parameter< const bool& >::type smooth_ex_post(smooth_ex_postSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type gamma(gammaSEXP);
    Rcpp::traits::input_parameter< const int >::type parametergrid_max_combinations(parametergrid_max_combinationsSEXP);
    Rcpp::traits::input_parameter< const double& >::type forget_past_performance(forget_past_performanceSEXP);
    Rcpp::traits::input_parameter< bool >::type allow_quantile_crossing(allow_quantile_crossingSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::NumericMatrix> >::type init_weights(init_weightsSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type loss_array(loss_arraySEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type regret_array(regret_arraySEXP);
    Rcpp::traits::input_parameter< const bool >::type trace(traceSEXP);
    rcpp_result_gen = Rcpp::wrap(online(y, experts, tau, lead_time, loss_function, loss_parameter, loss_gradient, method, method_var, basis_knot_distance, basis_knot_distance_power, basis_deg, forget_regret, soft_threshold, soft_threshold_ex_post, hard_threshold, hard_threshold_ex_post, fixed_share, fixed_share_ex_post, smooth_lambda, smooth_knot_distance, smooth_knot_distance_power, smooth_deg, smooth_ndiff, smooth_ex_post, gamma, parametergrid_max_combinations, forget_past_performance, allow_quantile_crossing, init_weights, loss_array, regret_array, trace));
    return rcpp_result_gen;
END_RCPP
}
// predict_online
Rcpp::List predict_online(Rcpp::List& object, cube& new_experts);
RcppExport SEXP _profoc_predict_online(SEXP objectSEXP, SEXP new_expertsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type object(objectSEXP);
    Rcpp::traits::input_parameter< cube& >::type new_experts(new_expertsSEXP);
    rcpp_result_gen = Rcpp::wrap(predict_online(object, new_experts));
    return rcpp_result_gen;
END_RCPP
}
// optimize_weights
vec optimize_weights(const vec& truth, const mat& experts, const bool& affine, const bool& positive, const bool& intercept, const bool& debias, const std::string& loss_function, const double& tau, const double& forget, const double& loss_scaling);
RcppExport SEXP _profoc_optimize_weights(SEXP truthSEXP, SEXP expertsSEXP, SEXP affineSEXP, SEXP positiveSEXP, SEXP interceptSEXP, SEXP debiasSEXP, SEXP loss_functionSEXP, SEXP tauSEXP, SEXP forgetSEXP, SEXP loss_scalingSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const vec& >::type truth(truthSEXP);
    Rcpp::traits::input_parameter< const mat& >::type experts(expertsSEXP);
    Rcpp::traits::input_parameter< const bool& >::type affine(affineSEXP);
    Rcpp::traits::input_parameter< const bool& >::type positive(positiveSEXP);
    Rcpp::traits::input_parameter< const bool& >::type intercept(interceptSEXP);
    Rcpp::traits::input_parameter< const bool& >::type debias(debiasSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type loss_function(loss_functionSEXP);
    Rcpp::traits::input_parameter< const double& >::type tau(tauSEXP);
    Rcpp::traits::input_parameter< const double& >::type forget(forgetSEXP);
    Rcpp::traits::input_parameter< const double& >::type loss_scaling(loss_scalingSEXP);
    rcpp_result_gen = Rcpp::wrap(optimize_weights(truth, experts, affine, positive, intercept, debias, loss_function, tau, forget, loss_scaling));
    return rcpp_result_gen;
END_RCPP
}
// optimize_betas
mat optimize_betas(const mat& truth, const cube& experts, const bool& affine, const bool& positive, const bool& intercept, const bool& debias, const std::string& loss_function, const vec& tau_vec, const double& forget, const double& loss_scaling, const sp_mat& basis, const mat& beta);
RcppExport SEXP _profoc_optimize_betas(SEXP truthSEXP, SEXP expertsSEXP, SEXP affineSEXP, SEXP positiveSEXP, SEXP interceptSEXP, SEXP debiasSEXP, SEXP loss_functionSEXP, SEXP tau_vecSEXP, SEXP forgetSEXP, SEXP loss_scalingSEXP, SEXP basisSEXP, SEXP betaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const mat& >::type truth(truthSEXP);
    Rcpp::traits::input_parameter< const cube& >::type experts(expertsSEXP);
    Rcpp::traits::input_parameter< const bool& >::type affine(affineSEXP);
    Rcpp::traits::input_parameter< const bool& >::type positive(positiveSEXP);
    Rcpp::traits::input_parameter< const bool& >::type intercept(interceptSEXP);
    Rcpp::traits::input_parameter< const bool& >::type debias(debiasSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type loss_function(loss_functionSEXP);
    Rcpp::traits::input_parameter< const vec& >::type tau_vec(tau_vecSEXP);
    Rcpp::traits::input_parameter< const double& >::type forget(forgetSEXP);
    Rcpp::traits::input_parameter< const double& >::type loss_scaling(loss_scalingSEXP);
    Rcpp::traits::input_parameter< const sp_mat& >::type basis(basisSEXP);
    Rcpp::traits::input_parameter< const mat& >::type beta(betaSEXP);
    rcpp_result_gen = Rcpp::wrap(optimize_betas(truth, experts, affine, positive, intercept, debias, loss_function, tau_vec, forget, loss_scaling, basis, beta));
    return rcpp_result_gen;
END_RCPP
}
// oracle
Rcpp::List oracle(arma::mat& y, cube& experts, Rcpp::NumericVector tau, const bool& affine, const bool& positive, const bool& intercept, const bool& debias, const std::string loss_function, const double& loss_parameter, const double& forget);
RcppExport SEXP _profoc_oracle(SEXP ySEXP, SEXP expertsSEXP, SEXP tauSEXP, SEXP affineSEXP, SEXP positiveSEXP, SEXP interceptSEXP, SEXP debiasSEXP, SEXP loss_functionSEXP, SEXP loss_parameterSEXP, SEXP forgetSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< arma::mat& >::type y(ySEXP);
    Rcpp::traits::input_parameter< cube& >::type experts(expertsSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type tau(tauSEXP);
    Rcpp::traits::input_parameter< const bool& >::type affine(affineSEXP);
    Rcpp::traits::input_parameter< const bool& >::type positive(positiveSEXP);
    Rcpp::traits::input_parameter< const bool& >::type intercept(interceptSEXP);
    Rcpp::traits::input_parameter< const bool& >::type debias(debiasSEXP);
    Rcpp::traits::input_parameter< const std::string >::type loss_function(loss_functionSEXP);
    Rcpp::traits::input_parameter< const double& >::type loss_parameter(loss_parameterSEXP);
    Rcpp::traits::input_parameter< const double& >::type forget(forgetSEXP);
    rcpp_result_gen = Rcpp::wrap(oracle(y, experts, tau, affine, positive, intercept, debias, loss_function, loss_parameter, forget));
    return rcpp_result_gen;
END_RCPP
}
// make_knots
vec make_knots(const double& kstep, const double& a, const int deg);
RcppExport SEXP _profoc_make_knots(SEXP kstepSEXP, SEXP aSEXP, SEXP degSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const double& >::type kstep(kstepSEXP);
    Rcpp::traits::input_parameter< const double& >::type a(aSEXP);
    Rcpp::traits::input_parameter< const int >::type deg(degSEXP);
    rcpp_result_gen = Rcpp::wrap(make_knots(kstep, a, deg));
    return rcpp_result_gen;
END_RCPP
}
// make_difference_matrix
mat make_difference_matrix(const vec& knots, const int& bdiff, const int deg);
RcppExport SEXP _profoc_make_difference_matrix(SEXP knotsSEXP, SEXP bdiffSEXP, SEXP degSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const vec& >::type knots(knotsSEXP);
    Rcpp::traits::input_parameter< const int& >::type bdiff(bdiffSEXP);
    Rcpp::traits::input_parameter< const int >::type deg(degSEXP);
    rcpp_result_gen = Rcpp::wrap(make_difference_matrix(knots, bdiff, deg));
    return rcpp_result_gen;
END_RCPP
}
// make_hat_matrix
mat make_hat_matrix(const vec& x, const double& kstep, const double& lambda, const double& bdiff, const int deg, const double& a);
RcppExport SEXP _profoc_make_hat_matrix(SEXP xSEXP, SEXP kstepSEXP, SEXP lambdaSEXP, SEXP bdiffSEXP, SEXP degSEXP, SEXP aSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const vec& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const double& >::type kstep(kstepSEXP);
    Rcpp::traits::input_parameter< const double& >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< const double& >::type bdiff(bdiffSEXP);
    Rcpp::traits::input_parameter< const int >::type deg(degSEXP);
    Rcpp::traits::input_parameter< const double& >::type a(aSEXP);
    rcpp_result_gen = Rcpp::wrap(make_hat_matrix(x, kstep, lambda, bdiff, deg, a));
    return rcpp_result_gen;
END_RCPP
}
// make_basis_matrix
sp_mat make_basis_matrix(const vec& x, const double& kstep, const int deg, const double& a);
RcppExport SEXP _profoc_make_basis_matrix(SEXP xSEXP, SEXP kstepSEXP, SEXP degSEXP, SEXP aSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const vec& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const double& >::type kstep(kstepSEXP);
    Rcpp::traits::input_parameter< const int >::type deg(degSEXP);
    Rcpp::traits::input_parameter< const double& >::type a(aSEXP);
    rcpp_result_gen = Rcpp::wrap(make_basis_matrix(x, kstep, deg, a));
    return rcpp_result_gen;
END_RCPP
}
// spline_fit
vec spline_fit(const vec& y, const vec& x, const double& lambda, const int& ndiff, const int& deg, const double& knot_distance, const double& knot_distance_power);
RcppExport SEXP _profoc_spline_fit(SEXP ySEXP, SEXP xSEXP, SEXP lambdaSEXP, SEXP ndiffSEXP, SEXP degSEXP, SEXP knot_distanceSEXP, SEXP knot_distance_powerSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const vec& >::type y(ySEXP);
    Rcpp::traits::input_parameter< const vec& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const double& >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< const int& >::type ndiff(ndiffSEXP);
    Rcpp::traits::input_parameter< const int& >::type deg(degSEXP);
    Rcpp::traits::input_parameter< const double& >::type knot_distance(knot_distanceSEXP);
    Rcpp::traits::input_parameter< const double& >::type knot_distance_power(knot_distance_powerSEXP);
    rcpp_result_gen = Rcpp::wrap(spline_fit(y, x, lambda, ndiff, deg, knot_distance, knot_distance_power));
    return rcpp_result_gen;
END_RCPP
}
// splines2_basis
mat splines2_basis(const vec& x, const vec& knots, const unsigned int deg, const vec& boundary_knots);
RcppExport SEXP _profoc_splines2_basis(SEXP xSEXP, SEXP knotsSEXP, SEXP degSEXP, SEXP boundary_knotsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const vec& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const vec& >::type knots(knotsSEXP);
    Rcpp::traits::input_parameter< const unsigned int >::type deg(degSEXP);
    Rcpp::traits::input_parameter< const vec& >::type boundary_knots(boundary_knotsSEXP);
    rcpp_result_gen = Rcpp::wrap(splines2_basis(x, knots, deg, boundary_knots));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_profoc_batch", (DL_FUNC) &_profoc_batch, 28},
    {"_profoc_loss", (DL_FUNC) &_profoc_loss, 7},
    {"_profoc_loss_grad_wrt_w", (DL_FUNC) &_profoc_loss_grad_wrt_w, 7},
    {"_profoc_pmin_arma", (DL_FUNC) &_profoc_pmin_arma, 2},
    {"_profoc_pmax_arma", (DL_FUNC) &_profoc_pmax_arma, 2},
    {"_profoc_diff_cpp", (DL_FUNC) &_profoc_diff_cpp, 3},
    {"_profoc_get_combinations", (DL_FUNC) &_profoc_get_combinations, 4},
    {"_profoc_set_default", (DL_FUNC) &_profoc_set_default, 2},
    {"_profoc_vec2mat", (DL_FUNC) &_profoc_vec2mat, 3},
    {"_profoc_mat2vec", (DL_FUNC) &_profoc_mat2vec, 1},
    {"_profoc_online", (DL_FUNC) &_profoc_online, 33},
    {"_profoc_predict_online", (DL_FUNC) &_profoc_predict_online, 2},
    {"_profoc_optimize_weights", (DL_FUNC) &_profoc_optimize_weights, 10},
    {"_profoc_optimize_betas", (DL_FUNC) &_profoc_optimize_betas, 12},
    {"_profoc_oracle", (DL_FUNC) &_profoc_oracle, 10},
    {"_profoc_make_knots", (DL_FUNC) &_profoc_make_knots, 3},
    {"_profoc_make_difference_matrix", (DL_FUNC) &_profoc_make_difference_matrix, 3},
    {"_profoc_make_hat_matrix", (DL_FUNC) &_profoc_make_hat_matrix, 6},
    {"_profoc_make_basis_matrix", (DL_FUNC) &_profoc_make_basis_matrix, 4},
    {"_profoc_spline_fit", (DL_FUNC) &_profoc_spline_fit, 7},
    {"_profoc_splines2_basis", (DL_FUNC) &_profoc_splines2_basis, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_profoc(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
