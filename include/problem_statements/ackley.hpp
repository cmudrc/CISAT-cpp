#ifndef ACKLEY_HPP
#define ACKLEY_HPP

#include <vector>
#include <cmath>
#include <iostream>

#include "../../include/utils/makerandom.hpp"

class Solution {
public:
    // Constants
    constexpr int number_of_move_ops = 20;
    constexpr long double upper_bound = 10;
    constexpr long double lower_bound = -10;

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