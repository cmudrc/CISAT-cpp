#ifndef STATS_HPP
#define STATS_HPP

#include <vector>
#include <cstdlib>
#include <cmath>
#include <numeric>
#include <cfloat>
#include <deque>

using namespace std;

// Function to return maximum value of vector
long double vector_max(vector<long double> v);

// Function to return minimum value of vector
long double vector_min(vector<long double> v);

// Compute mean of a vector
long double mean(vector<long double> x);

// Compute mean of a deque
long double stdev(deque<long double> x);

// Compute standard deviation of a list
long double stdev(deque<long double> x);

// Compute the x value for the optimium of a linear regression
vector<long double> quad_max(vector<long double> x, vector<long double> y);

vector<long double> gauss(vector< vector<long double> > A);

#endif