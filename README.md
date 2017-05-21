# Parsing Expression Grammars in Rcpp
[![Travis-CI Build Status](https://travis-ci.org/Ironholds/piton.svg?branch=master)](https://travis-ci.org/Ironholds/piton) ![downloads](http://cranlogs.r-pkg.org/badges/grand-total/piton)

`piton` provides platform-independent [parsing expression grammar](https://en.wikipedia.org/wiki/Parsing_expression_grammar) support in Rcpp. It wraps the [PEGTL](https://github.com/taocpp/PEGTL) library by Colin Hirsch and Daniel Frey, which is header-only and so can be imported into other packages.

## Use

`piton` itself is not designed for straight-up useR use - instead, it's a developer package. If you're interested in implementing a PEG using it, you need to:

1. Link `piton` into your package as a dependency, using `//[[Rcpp::depends()]]` (see [this post](http://gallery.rcpp.org/articles/a-first-boost-example/) for an example of how it works);
2. `#include <pegtl.hpp>`
3. Write and expose your grammar
4. Done!

The [PEGTL docs](https://github.com/taocpp/PEGTL/blob/master/doc/README.md) contain quite a bit of documentation on how the underlying library works, and [various examples of PEGs](https://github.com/taocpp/PEGTL/blob/master/doc/Contrib-and-Examples.md) are included within the package itself.


## Installation

Once it's on CRAN:

```
install.packages("piton")
```

Until then:

```
devtools::install_github("ironholds/piton")
```
