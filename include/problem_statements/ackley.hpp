#ifndef ACKLEY_HPP
#define ACKLEY_HPP

#define THIS_IS_A_THING 30

#include <vector>
#include <cmath>
#include <iostream>

#include "../../include/utils/makerandom.hpp"

class Solution {
public:
    // Constants
    int number_of_move_ops;
    long double ubnd;
    long double lbnd;

    // Functions
    Solution(void);
    void compute_quality(void);
    void apply_move_operator(int n, long double size);

    // Variables
    int id;
    long double quality;
    std::vector<long double> x;
};

#endif