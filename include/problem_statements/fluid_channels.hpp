#ifndef PROBLEM_STATEMENTS__FLUID_CHANNELS_HPP
#define PROBLEM_STATEMENTS__FLUID_CHANNELS_HPP

#include <iostream>
#include <cmath>
#include "graph.hpp"
#include "../utilities/make_random.hpp"
#include "../utilities/write_x3d.hpp"

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
    static const long double fluid_n;
    static const long double fluid_C;

    // Variables
    int solution_id;
    static int solution_counter;

    // Inlet location
    static std::vector< std::map<std::string, long double> > seed_graph_parameters;
    std::vector<int> inlet_keys;
    std::vector<int> outlet_keys;

    // Functions
    void compute_quality(void);
    void create_seed_graph(void);

    // Move operators
    void add_pipe(int n1, int n2, long double d);
    void add_junction(long double x, long double y, long double z, bool moveable);
    void add_midpoint_junction(int e);
    void remove_pipe(int e);
    void remove_junction(int n);

    int is_valid(void);
    long double euclidean_distance(int n1, int n2);

};


// This function returns a thing important for hardy cross method
template <typename Type1, typename Type2>
Type1 fluid_pow(Type1 Q, Type2 n) {
    return Q * std::pow(std::abs(Q), n-1);
}


#endif
