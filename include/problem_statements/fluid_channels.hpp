#ifndef PROBLEM_STATEMENTS__FLUID_CHANNELS_HPP
#define PROBLEM_STATEMENTS__FLUID_CHANNELS_HPP

#include <iostream>
#include <cmath>
#include "graph.hpp"
#include "../utilities/make_random.hpp"

class Solution : public Graph{
public:
    // Constants
    static const unsigned long number_of_move_ops;
    static const unsigned long number_of_objectives;
    static const long double goal;

    // Variables
    std::vector<long double> quality;
    std::vector<std::vector< std::vector<int> > > move_options;

    // Functions
    Solution(void);
    void get_valid_moves(void);
    void apply_move_operator(int move_type, int move_number);
    static void print_surface_characteristics(void);

private:
    // Constants
    static const std::string name;

    // Variables
    int solution_id;
    static int solution_counter;

    // Inlet location
    static const std::vector< std::vector<long double>> in_xyz;
    static const std::vector< std::vector<long double>> out_xyz;
    static const std::vector<long double> in_flow;
    static const std::vector<long double> out_flow;

    // Functions
    void compute_quality(void);

    // Move operators
    void add_pipe(int n1, int n2, long double d1, long double d2);
    void add_junction(long double x, long double y, long double z, bool moveable);
    void add_midpoint_junction(int e);
    void remove_pipe(int e);
    void remove_junction(int n);

    void is_valid(void);
    long double euclidean_distance(int n1, int n2);

};


#endif
