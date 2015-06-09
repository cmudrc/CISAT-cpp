#ifndef PROBLEM_STATEMENTS__FLUID_CHANNELS_HPP
#define PROBLEM_STATEMENTS__FLUID_CHANNELS_HPP

#include <iostream>
#include <cmath>
#include "graph.hpp"

class Solution : public Graph{
public:
    // Constants
    static const unsigned long number_of_move_ops;
    static const unsigned long number_of_objectives;
    static const long double goal;

    // Variables
    std::vector<long double> quality;

    // Functions
    Solution(void);
    void apply_move_operator(int n, long double size);
    static void print_surface_characteristics();

private:
    // Constants
    static const std::string name;

    // Variables
    int solution_id;
    static int solution_counter;

    // Inlet location
    static const std::vector< std::vector<long double>> inlets;
    static const std::vector< std::vector<long double>> outlets;

    // Functions
    void compute_quality(void);
    void add_pipe(int n1, int n2, long double d1, long double d2);
    void add_junction(long double x, long double y, long double z);
    void add_junction(int e);

};


#endif
