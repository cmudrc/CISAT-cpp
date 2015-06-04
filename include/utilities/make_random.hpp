#ifndef UTILITIES__MAKE_RANDOM_HPP
#define UTILITIES__MAKERANDOM_HPP

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// Function to return a uniform long double
long double uniform(long double ub, long double lb);

// Function to return a uniform int
int uniform_int(int ub, int lb);

// Function to seed wrt time
void seed_time(void);

// Function to return a uniform random vector
vector<long double> random_vector(unsigned long D, long double ub, long double lb);

// Weighted random choice function
int weighted_choice(vector<long double> x);

#endif