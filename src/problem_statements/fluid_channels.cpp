#include "../../include/problem_statements/fluid_channels.hpp"

// Integer to assign unique IDs to solutions
int Solution::solution_counter = 0;
const unsigned long Solution::number_of_move_ops = 2;
const unsigned long Solution::number_of_objectives = 1;
const std::string Solution::name = "Fluid Problem";
const long double Solution::goal = 0.1;
const std::vector< std::vector<long double>> Solution::inlets = {{1, 2, 3}, {4, 5, 6}};
const std::vector< std::vector<long double>> Solution::outlets = {{7, 8, 9}, {10, 11, 12}};

Solution::Solution(void) {
    // Give the solution a unique ID and increment the counter
    solution_id = solution_counter;
    solution_counter++;

    // Create nodes at each of the specified locations
    for(int i=0; i < inlets.size(); i++) {
        add_junction(inlets[i][0], inlets[i][1], inlets[i][2]);
        nodes[node_id_counter].parameters["moveable"] = false;
    }
    for(int i=0; i < inlets.size(); i++) {
        add_junction(outlets[i][0], outlets[i][1], outlets[i][2]);
        nodes[node_id_counter].parameters["moveable"] = false;
    }

    // Initialize quality
    quality.assign(number_of_objectives, 0);
    compute_quality();
}

void Solution::compute_quality(void) {
    quality[0] = 1;
}

void Solution::apply_move_operator(int n, long double size) {
}

void Solution::add_pipe(int n1, int n2, long double d1, long double d2) {
    // Add an edge
    add_edge(n1, n2);

    // Add parameters for the edges
    edges[edge_id_counter].parameters["d1"] = d1;
    edges[edge_id_counter].parameters["d2"] = d1;

    // Compute the length
    edges[edge_id_counter].parameters["L"] = std::sqrt(
              std::pow(nodes[n1].parameters["x"] - nodes[n2].parameters["x"], 2)
            + std::pow(nodes[n1].parameters["y"] - nodes[n2].parameters["y"], 2)
            + std::pow(nodes[n1].parameters["z"] - nodes[n2].parameters["z"], 2)
    );

    //
}

void Solution::add_junction(long double x, long double y, long double z) {
    // Add the node
    add_node();

    // Add the coordinates
    nodes[node_id_counter].parameters["x"] = x;
    nodes[node_id_counter].parameters["y"] = y;
    nodes[node_id_counter].parameters["z"] = z;
}

void Solution::add_junction(int e) {
    int n1 = edges[e].initial_node;
    int n2 = edges[e].terminal_node;

    // Make a new node
}

void Solution::print_surface_characteristics() {
    std::cout << "Problem Characteristics" << std::endl;
    std::cout << "\tName: " << name << std::endl;
    std::cout << "\tGoal: " << goal << std::endl;
    std::cout << "\tNumber of move operators: " << number_of_move_ops << std::endl;
}