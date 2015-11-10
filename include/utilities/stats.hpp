//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  include
//  └─┴─────┘  ││   └─utilities
//             ││      └─stats.hpp

#ifndef UTILITIES__STATS_HPP
#define UTILITIES__STATS_HPP

#include <vector>
#include <cstdlib>
#include <cmath>
#include <numeric>
#include <cfloat>
#include <deque>
#include "./custom_print.hpp"
#include "./optimization.hpp"

// Function to return maximum value of vector
long double vector_maximum(std::vector<long double> v);

// Function that returns the index of the maximum value
long vector_argmax(std::vector<long double> v);

// Function to return minimum value of vector
long double vector_minimum(std::vector<long double> v);

// Function that returns the index of the minimum value
long vector_argmin(std::vector<long double> v);

// Compute mean of a vector
long double mean(std::vector<long double> x);

// Compute mean of a deque
long double stdev(std::deque<long double> x);

// Compute standard deviation of a list
long double stdev(std::deque<long double> x);

// Applies weighting
long double apply_weighting(std::vector<long double> a, std::vector<long double> b);

// Computes cliff's delta for
long double pareto_cliff_delta(std::vector<std::vector<long double> > x, std::vector<std::vector<long double> > y);

// Computes signum, or sign
template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

// Logistic sigmoidal function for neural networks
template <typename Type>
Type logistic_sigmoid(Type x) {
    return 1.0/(1.0 + std::exp(-x));
}

#endif