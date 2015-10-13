//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  include
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─structure.hpp

#ifndef PROBLEM_STATEMENTS__STRUCTURE_HPP
#define PROBLEM_STATEMENTS__STRUCTURE_HPP

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
    std::vector<std::vector< std::vector<int> > > move_options;

    // Functions
    Solution(bool);
    Solution(void);
    void get_valid_moves(void);
    void apply_move_operator(int move_type, int move_number);
    static void print_surface_characteristics(void);
    void save_as_x3d(std::string save_to_file);

private:
    // Constants
    static const std::string name;

    // Fluid constants
    static const long double E;
    static const long double Fy;

    // Pipe diameters
    static const std::vector< long double > pipe_diam;

    // Variables
    int solution_id;
    static int solution_counter;

    // Inlet location
    static std::vector< std::map<std::string, long double> > seed_graph_parameters;

    // Functions
    void compute_quality(void);
    void create_seed_graph(void);

    // Move operators
    void add_member(int n1, int n2, int d, bool editable);
    void add_joint(long double x, long double y, long double z, bool editable);
    void remove_member(int e);
    void remove_joint(int n);
    void increase_member_size(int e);
    void decrease_member_size(int e);
    void move_joint(int n, long double dx, long double dy, long double dz);
    void brace_member(int e);
    void add_joint_and_attach(long double x, long double y, long double z);

    int is_valid(void);
};

#endif
