testthat::context("Test example sum function")

testthat::test_that("The sum function works", {
  testthat::expect_equal(peg_sum("12,14,19,2"), 47)
})

testthat::test_that("The sum function works vectorised", {
  testthat::expect_equal(length(peg_sum(c("12,14,19,2", NA_character_))), 2)
})

testthat::test_that("The sum function works with NAs", {
  testthat::expect_true(is.na(peg_sum(NA_character_)))
})
