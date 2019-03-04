
<!-- README.md is generated from README.Rmd. Please edit that file -->

# compact

<!-- badges: start -->

<!-- badges: end -->

This is just an experimentation around R \> 3.5.0 compact integer
sequences

## Installation

You can install the dev version:

``` r
remotes::install_github("romainfrancois/compact")
```

## Example

``` r
library(compact)

s <- 1:10
is_compact(s)
#> [1] TRUE
compact_length(s)
#> [1] 10
compact_is_expanded(s)
#> [1] FALSE
compact_first(s)
#> [1] 1
compact_increment(s)
#> [1] 1
```
