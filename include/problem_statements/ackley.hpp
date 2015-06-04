#ifndef PROBLEM_STATEMENTS__ACKLEY_HPP
#define PROBLEM_STATEMENTS__ACKLEY_HPP

#include <vector>
#include <cmath>
#include <iostream>

#include "../../include/utilities/make_random.hpp"

class Solution {
public:
    // Constants
    static constexpr int         number_of_move_ops =  20;
    static constexpr long double upper_bound        =  10;
    static constexpr long double lower_bound        = -10;

    // Functions
    Solution(void);
    void compute_quality(void);
    void apply_move_operator(int n, long double size);

    // Variables
    int id;
    long double quality;
    vector<long double> x;
};

#endif