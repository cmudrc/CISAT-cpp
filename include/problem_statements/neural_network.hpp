//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  include
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─neural_network.hpp

#if PROBLEM_STATEMENT == NEURAL
#ifndef PROBLEM_STATEMENTS__NEURAL_NETWORK_HPP
#define PROBLEM_STATEMENTS__NEURAL_NETWORK_HPP

#include <iostream>
#include <cmath>
#include "graph.hpp"
#include "../utilities/make_random.hpp"
#include "../utilities/write_x3d.hpp"
#include "../utilities/custom_print.hpp"

class Solution : public Graph{
public:
    // Constants
    static const unsigned long number_of_move_ops;
    static const unsigned long number_of_objectives;
    static const long double goal;

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

    // Variables
    int solution_id;
    static int solution_counter;

    // Inlet location
    static std::vector< std::map<std::string, long double> > seed_graph_parameters;

    // Functions
    void compute_quality(void);
    void create_seed_graph(void);

    // Move operators for Campbell
    // TODO: Figure out what the hell these are
    void connect_with_edge(void);          // rule 1
    void connecte_with_noded_edge(void);   // rule 2
    void replace_with_noded_edge(void);    // rule 3
    void bypass_connection(void);          // rule 4
    // rule 5
    void grow_hidden_layer(); // rule 6

    bool is_valid(void);
};

#endif
#endif