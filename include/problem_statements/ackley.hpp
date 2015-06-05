#ifndef PROBLEM_STATEMENTS__ACKLEY_HPP
#define PROBLEM_STATEMENTS__ACKLEY_HPP

#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>

#include "../../include/utilities/make_random.hpp"

class Solution {
public:
    // Constants
    static const int number_of_move_ops;
    static const long double goal;

    // Variables
    long double quality;

    // Functions
    Solution(void);
    void apply_move_operator(int n, long double size);
    void print_surface_characteristics();

private:
    // Constants
    static const string name;
    static const long double upper_bound;
    static const long double lower_bound;

    // Variables
    int solution_id;
    static int solution_counter;
    vector<long double> x;

    // Functions
    void compute_quality(void);
};

#endif