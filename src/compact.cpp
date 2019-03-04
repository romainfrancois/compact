#include <Rcpp.h>

#include <R.h>
#include <Rinternals.h>
#include <Rversion.h>

#if R_VERSION < R_Version(3, 6, 0)

// workaround because R's <R_ext/Altrep.h> not so conveniently uses `class`
// as a variable name, and C++ is not happy about that
//
// SEXP R_new_altrep(R_altrep_class_t class, SEXP data1, SEXP data2);
//
#define class klass

// Because functions declared in <R_ext/Altrep.h> have C linkage
extern "C" {
#include <R_ext/Altrep.h>
}

// undo the workaround
#undef class

#else
#include <R_ext/Altrep.h>
#endif

#define COMPACT_SEQ_INFO(x) R_altrep_data1(x)
#define COMPACT_SEQ_EXPANDED(x) R_altrep_data2(x)

#define COMPACT_LENGTH(info) REAL0(info)[0]
#define COMPACT_FIRST(info) REAL0(info)[1]
#define COMPACT_INCR(info) REAL0(info)[2]

//' @export
// [[Rcpp::export]]
SEXP is_compact(SEXP x) {
  static SEXP s_compact_intseq = Rf_install("compact_intseq");
  static SEXP s_compact_realseq = Rf_install("compact_realseq");

  if (!ALTREP(x)) return Rf_ScalarLogical(FALSE);
  SEXP klass = CAR(ATTRIB(ALTREP_CLASS(x)));
  return Rf_ScalarLogical(klass == s_compact_intseq || klass == s_compact_realseq) ;
}

//' @export
// [[Rcpp::export]]
SEXP compact_info(SEXP x){
  return COMPACT_SEQ_INFO(x);
}

//' @export
// [[Rcpp::export]]
SEXP compact_is_expanded(SEXP x){
  return Rf_ScalarLogical(!Rf_isNull(COMPACT_SEQ_EXPANDED(x)));
}

//' @export
// [[Rcpp::export]]
SEXP compact_length(SEXP x) {
  SEXP info = COMPACT_SEQ_INFO(x);
  return Rf_ScalarReal(COMPACT_LENGTH(info));
}

//' @export
// [[Rcpp::export]]
SEXP compact_first(SEXP x) {
  SEXP info = COMPACT_SEQ_INFO(x);
  return Rf_ScalarReal(COMPACT_FIRST(info));
}

//' @export
// [[Rcpp::export]]
SEXP compact_increment(SEXP x) {
  SEXP info = COMPACT_SEQ_INFO(x);
  return Rf_ScalarReal(COMPACT_INCR(info));
}
