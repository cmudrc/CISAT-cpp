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
#include "../utilities/stats.hpp"

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
    void apply_move_operator(int move_type);
    void save_as_x3d(std::string save_to_file);

private:
    // Constants
    static const std::string name;

    // Fluid constants
    static const long double E;
    static const long double Fy;

    // Pipe diameters
    static const std::vector< long double > member_radius;
    static const std::vector< long double > wall_thickness;

    // Variables
    int solution_id;
    static int solution_counter;

    // Inlet location
    static std::vector< std::map<std::string, long double> > seed_node_parameters;
    static std::vector< std::map<std::string, long double> > seed_edge_parameters;

    // Functions
    void compute_quality(void);
    void compute_truss_forces(void);
//    void compute_frame_forces(void);
    void create_seed_graph(void);

    // Move operators
    void add_member(int n1, int n2, int d, bool editable);
    void add_member(void);
    void add_joint(long double x, long double y, long double z, bool editable);
    void remove_member(void);
    void remove_joint(void);
    void change_size_single(void);
    void change_size_all(void);
    void move_joint(void);
    void add_joint_and_attach(void);

    int is_valid(void);
    void update_sectional_properties(int e);
    void update_length(int e);
};

#endif
