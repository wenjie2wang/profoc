#' @template function_online
#'
#' @template param_y
#' @template param_experts
#' @template param_tau
#' @template param_intercept
#' @template param_loss_function
#' @template param_loss_parameter
#' @template param_ex_post_smooth
#' @template param_ex_post_fs
#' @template param_smooth_lambda
#' @template param_method
#' @param method_var Allows to calculate slight variations of the BOA
#' algorithm
#' @param forget_regret Share of past regret not to be considered, resp. to be
#' forgotten in every iteration of the algorithm. Defaults to 0.
#' @template param_forget_performance
#' @template param_fixed_share
#' @param gamma Scaling parameter for the learning rate.
#' @template param_smooth_ndiff
#' @template param_smooth_deg
#' @template param_basis_deg_online
#' @template param_smooth_knot_distance
#' @template param_basis_knot_distance_online
#' @template param_smooth_knot_distance_power
#' @template param_basis_knot_distance_power
#' @param gradient Determines if a linearized version of the loss is used.
#' @param loss_array User specified loss array. If specified, the loss will not be calculated by profoc.
#' @param regret_array User specified regret array. If specifiec, the regret will not be calculated by profoc.
#' @template param_trace
#' @param init_weights Matrix of dimension Kx1 or KxP used as starting weights. Kx1 represents the constant solution with equal weights over all P whereas specifiying a KxP matrix allows different starting weights for each P.
#' @template param_lead_time
#' @template param_allow_quantile_crossing
#' @template param_soft_threshold
#' @template param_ex_post_soft_threshold
#' @template param_hard_threshold
#' @template param_ex_post_hard_threshold
#' @template param_max_parameter_combinations
#' @usage online(y, experts, tau, intercept = FALSE, loss_function = "quantile",
#' loss_parameter = 1, ex_post_smooth = FALSE, ex_post_fs = FALSE,
#' smooth_lambda = -Inf, method = "boa", method_var = "A", forget_regret = 0,
#' forget_performance = 0, fixed_share = 0, gamma = 1, smooth_ndiff = 1, smooth_deg = 3,
#' basis_deg = 3,
#' smooth_knot_distance = c(2^seq(log(1/(length(tau)+1),2)-1, -1, length=5),1),
#' basis_knot_distance = c(2^seq(log(1/(length(tau)+1),2)-1, -1, length=5),1),
#' smooth_knot_distance_power = 1, basis_knot_distance_power = 1,
#' gradient = TRUE, loss_array = NULL, regret_array = NULL,
#' trace = TRUE, init_weights = NULL, lead_time = 0, allow_quantile_crossing = FALSE,
#' soft_threshold = -Inf, ex_post_soft_threshold = FALSE, hard_threshold = -Inf,
#' ex_post_hard_threshold = FALSE, max_parameter_combinations = 100)
#' @export
online <- function(x = NULL, ...) {
    UseMethod("online", x)
}

online.default <- function(...) {
    online_default(...)
}