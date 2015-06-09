#ifndef UTILITIES__STATS_HPP
#define UTILITIES__STATS_HPP

#include <vector>
#include <cstdlib>
#include <cmath>
#include <numeric>
#include <cfloat>
#include <deque>

// Function to return maximum value of vector
long double vector_maximum(std::vector<long double> v);

// Function to return minimum value of vector
long double vector_minimum(std::vector<long double> v);

// Compute mean of a vector
long double mean(std::vector<long double> x);

// Compute mean of a deque
long double stdev(std::deque<long double> x);

// Compute standard deviation of a list
long double stdev(std::deque<long double> x);

std::vector<long double> gauss(std::vector< std::vector<long double> > A);

long double apply_weighting(std::vector<long double> a, std::vector<long double> b);

#endif