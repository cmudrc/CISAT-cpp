#ifndef UTILITIES__OPTIMIZATION_HPP
#define UTILITIES__OPTIMIZATION_HPP

#include <vector>
#include "./stats.hpp"
#include "./matrix_operations.hpp"

// Compute the x value of the optimium of a linear regression
std::vector<long double> quad_max(std::vector<long double> x, std::vector<long double> y);

// Computes the pareto front for a set of data
std::vector<bool> get_pareto_front(std::vector< std::vector<long double> > y);

// Returns the pareto tiers for a data set
std::vector<int> get_pareto_tiers(std::vector< std::vector<long double> > y);

// Performs a Pareto comparison
long double pareto_comparison(std::vector<long double> x, std::vector<long double> y);

#endif
