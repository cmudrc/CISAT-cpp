//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  include
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─structure.hpp

#if PROBLEM_STATEMENT == TRUSS
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

    // Functions
    Solution(bool);
    Solution(void);
    void apply_move_operator(int rule_number);
    void save_as_x3d(std::string save_to_file);

private:
    // Constants
    static const std::string name;

    // Material constants
    static const long double E;
    static const long double Fy;
    static const long double density;

    // Member parameters
    static const std::vector< long double > member_radius;
    static const std::vector< long double > wall_thickness;

    // Miscellaneous variables
    int solution_id;
    static int solution_counter;

    // Saving the global FOS
    long double FOS;
    long double mass;
    long double cond;

    // Inlet location
    static std::vector< std::map<std::string, long double> > seed_node_parameters;
    static std::vector< std::map<std::string, long double> > seed_edge_parameters;

    // Functions
    void compute_quality(void);
    void compute_truss_forces(void);
//    void compute_frame_forces(void);
    void create_seed_graph(void);

    // Move operators for McComb grammar
    void add_member(int n1, int n2, int d, bool editable);
    void add_member(void);
    void add_joint(long double x, long double y, long double z, bool editable);
    void remove_member(void);
    void remove_joint(void);
    void change_size_single(void);
    void change_size_all(void);
    void move_joint(void);
    void add_joint_and_attach(void);

    // Move operators unique to Shea Frame grammar
    #if RULE_SET == SHEA_FRAME
        void biad_to_triad(void);
        void triad_to_biad(void);
    #endif

    // Move operators unique to Shea Truss grammar
    #if RULE_SET == SHEA_TRUSS
        void flip_flop(void);
        void add_bisection(void);
        void remove_bisection(void);
        void add_trisection(void);
        void remove_trisection(void);
    #endif

    // Random additional utilities
    bool is_valid(void);
    void update_sectional_properties(int e);
    void update_length(int e);
    void calculate_member_mass(int e);
};

#endif
#endif
