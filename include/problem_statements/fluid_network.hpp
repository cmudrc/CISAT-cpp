//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  include
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─fluid_network.hpp

#if PROBLEM_STATEMENT == FLUID
#ifndef PROBLEM_STATEMENTS__FLUID_NETWORK_HPP
#define PROBLEM_STATEMENTS__FLUID_NETWORK_HPP

#include <iostream>
#include <cmath>
#include "graph.hpp"
#include "../utilities/make_random.hpp"
#include "../utilities/write_x3d.hpp"
#include "../utilities/custom_print.hpp"
#include "../utilities/stats.hpp"

class Solution : public Graph{
public:
    // Constants
    static const unsigned long number_of_move_ops;
    static const unsigned long number_of_objectives;
    static const std::vector<long double> goal;

    // Variables
    std::vector<long double> quality;

    // Functions
    Solution(bool);
    Solution(void);
    void apply_move_operator(int move_type);
    void save_as_x3d(std::string save_to_file);

private:
    // Constants
    static const std::string name;

    // Fluid constants
    static const long double fluid_u;
    static const long double target_flowrate;

    // Pipe diameters
    static const std::vector< long double > pipe_diam;

    // Variables
    int solution_id;
    static int solution_counter;
    long double cond;

    // Inlet location
    static std::vector< std::map<std::string, long double> > seed_node_parameters;
    static std::vector< std::map<std::string, long double> > seed_edge_parameters;

    // Functions
    void compute_quality(void);
    void compute_fluid_solution(void);
    void create_seed_graph(void);

    // Move operators for McComb
    void add_pipe(int n1, int n2, int d, bool editable);
    void add_pipe(void);
    void add_junction(long double x, long double y, long double z, bool editable);
    void remove_pipe(void);
    void remove_junction(void);
    void change_pipe_size(void);
    void add_midpoint_junction(void);
    void move_junction(void);

    // Move operators exclusive to Campbell
    void inlet_to_outlet(void);
    void intermediate_inlet(void);
    void intermediate_outlet(void);

    //Utilities
    void clean_dangly_bits(void);
    int is_valid(void);
    void update_length(int e);
};

#endif
#endif
