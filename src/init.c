#include <R.h>
#include <Rinternals.h>
#include <stdlib.h>
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP piton_peg_sum(SEXP);

static const R_CallMethodDef CallEntries[] = {
  {"piton_peg_sum", (DL_FUNC) &piton_peg_sum, 1},
  {NULL, NULL, 0}
};

void R_init_piton(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
