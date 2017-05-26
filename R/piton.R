#' @title Parsing Expression Grammars in Rcpp
#' @name piton
#' @description This package wraps the PEGTL library to make Parsing Expression Grammars
#' available to R/C++ developers. As an exported, header-only package, it can be included
#' in other Rcpp codebases using \code{depends} functionality, and is platform-independent.
#'
#' @seealso the \href{https://github.com/Ironholds/piton/blob/master/README.md}{README},
#' or \code{\link{peg_sum}} for an example.
#' @useDynLib piton, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @docType package
#' @aliases piton piton-package
NULL
