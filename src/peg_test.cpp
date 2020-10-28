#include <Rcpp.h>
#include <pegtl.hpp>
using namespace tao::TAO_PEGTL_NAMESPACE;

namespace double_
{

struct plus_minus : opt< one< '+', '-' > > {};
struct dot : one< '.' > {};

           struct inf : seq< istring< 'i', 'n', 'f' >,
                        opt< istring< 'i', 'n', 'i', 't', 'y' > > > {};

           struct nan : seq< istring< 'n', 'a', 'n' >,
                        opt< one< '(' >,
                                    plus< alnum >,
                                    one< ')' > > > {};

           template< typename D >
           struct number : if_then_else< dot,
                           plus< D >,
                           seq< plus< D >, opt< dot, star< D > > > > {};

           struct e : one< 'e', 'E' > {};
           struct p : one< 'p', 'P' > {};
           struct exponent : seq< plus_minus, plus< digit > > {};

           struct decimal : seq< number< digit >, opt< e, exponent > > {};
           struct binary : seq< one< '0' >, one< 'x', 'X' >, number< xdigit >, opt< p, exponent > > {};

           struct grammar : seq< plus_minus, sor< decimal, binary, inf, nan > > {};
           // clang-format on

}  // double_

namespace sum
{
struct padded_double
  : pad< double_::grammar, space >
{
};

struct double_list
  : list< padded_double, one< ',' > >
{
};

struct grammar
  : seq< double_list, eof >
{
};

template< typename Rule >
struct action
  : nothing< Rule >
{
};

template<>
struct action< double_::grammar >
{
  template< typename Input >
  static void apply( const Input& in, double& sum )
  {
    // assume all values will fit into a C++ double
    char* ptr = const_cast< char* >( in.end() );
    sum += std::strtod( const_cast< char* >( in.begin() ), &ptr );
  }
};

} // namespace sum


void sum_single(Rcpp::CharacterVector& x, Rcpp::NumericVector& out, int i){

  if(x[i] == R_NaString){
    out[i] = R_NaReal;
    return;
  }
  const std::string holding = Rcpp::as<std::string>(x[i]);
  double output = 0.0;

  memory_input<> din(holding, "moot");

  if( parse< sum::grammar, sum::action >(din, output)) {
    out[i] = output;
  } else {
    out[i] = R_NaReal;
  }
}

//'@title Example PEG
//'@description an example of a Parsing Expression Grammar
//'(PEG) that takes a comma-separated string of digits and
//'sums them together
//'
//'@param x a vector of strings, each containing a comma-separated
//'set of digits
//'
//'@return a vector of numbers, containing either the sum of
//'the equivalent element of \code{x} or (if the element
//'could not be parsed) \code{NA}.
//'
//'@examples
//'# Simple example
//'peg_sum("1,2, 5, 91, 34")
//'
//'@export
//[[Rcpp::export]]
Rcpp::NumericVector peg_sum(Rcpp::CharacterVector x){

  unsigned int input_size = x.size();
  Rcpp::NumericVector output(input_size);

  for(unsigned int i = 0; i < input_size; i++){
    sum_single(x, output, i);
  }

  return output;
}
