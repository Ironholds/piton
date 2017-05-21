#include <Rcpp.h>
using namespace Rcpp;
#include <pegtl.hpp>

using namespace tao::TAOCPP_PEGTL_NAMESPACE;

namespace double_
{
// A grammar for doubles suitable for std::stod without locale support.
// See also: http://en.cppreference.com/w/cpp/string/basic_string/stof

using namespace tao::TAOCPP_PEGTL_NAMESPACE;

// clang-format off
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

void sum_single(CharacterVector& x, NumericVector& out, int i){

  if(x[i] == NA_STRING){
    out[i] = NA_REAL;
    return;
  }

  const std::string holding = Rcpp::as<std::string>(x[i]);
  double output;

  memory_input<> din(holding, "moot");

  if( parse< sum::grammar, sum::action >(din, output)) {
    out[i] = output;
  } else {
    out[i] = NA_REAL;
  }
}

//[[Rcpp::export]]
NumericVector peg_sum(CharacterVector x){

  unsigned int input_size = x.size();
  NumericVector output(input_size);

  for(unsigned int i = 0; i < input_size; i++){
    sum_single(x, output, i);
  }

  return output;
}
