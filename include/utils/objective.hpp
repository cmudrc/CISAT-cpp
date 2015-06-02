#ifndef OBJECTIVE_HPP
#define OBJECTIVE_HPP

#include <vector>
#include <cmath>

using namespace std;

// Define the Griewank function
long double griewank(vector<long double> x);

// Define the Griewank function
long double ackley(vector<long double> x);

// Define the Griewank function
long double rastigrin(vector<long double> x);

#endif