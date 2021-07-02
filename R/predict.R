#' Predict method for online models
#' Calculates predictions based on new expert advice.
#' This does not update weights. If new observations are available
#' use update instead. The latter updates and computes predictions.
#' @param object Object of class inheriting from 'online'
#' @param new_experts new expert advices
#' @export
predict.online <- function(object, new_experts) {
    predict_online(object, new_experts)
}