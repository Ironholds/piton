# Parsing Expression Grammars in Rcpp
[![Travis-CI Build Status](https://travis-ci.org/Ironholds/piton.svg?branch=master)](https://travis-ci.org/Ironholds/piton) ![downloads](http://cranlogs.r-pkg.org/badges/grand-total/piton)

`piton` provides platform-independent [parsing expression grammar](https://en.wikipedia.org/wiki/Parsing_expression_grammar) support in Rcpp. It wraps the [PEGTL](https://github.com/taocpp/PEGTL) library by Colin Hirsch and Daniel Frey, which is header-only and so can be imported into other packages.

Please note that this project is released with a [Contributor Code of Conduct](https://github.com/Ironholds/piton/blob/master/CONDUCT.md). By participating in this project you agree to abide by its terms.

## Use

An example of PEGs is included in the package, and takes a comma-separated set of
numbers and sums them together:

```
library(piton)

peg_sum("1,2,  5, 91, 34")
[1] 133
```

`piton` itself is not designed for straight-up useR use - instead, it's a developer package. If you're interested in implementing a PEG using it, you need to:

1. Link `piton` into your package as a dependency, using `//[[Rcpp::depends()]]` (see [this post](http://gallery.rcpp.org/articles/a-first-boost-example/) for an example of how it works);
2. `#include <pegtl.hpp>`
3. Write and expose your grammar
4. Done!

The [PEGTL docs](https://github.com/taocpp/PEGTL/blob/master/doc/README.md) contain quite a bit of documentation on how the underlying library works, and [various examples of PEGs](https://github.com/taocpp/PEGTL/blob/master/doc/Contrib-and-Examples.md) are included within the package itself. Integration with Rcpp is pretty clean, although developers may benefit from not explicitly using the Rcpp namespace due to a couple of collisions with the `PEGTL` namespace.

## Installation

On CRAN:

```
install.packages("piton")
```

And for the development version:

```
devtools::install_github("ironholds/piton")
```
