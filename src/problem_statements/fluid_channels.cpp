#include "../../include/problem_statements/fluid_channels.hpp"

// Integer to assign unique IDs to solutions
int Solution::solution_counter = 0;
const unsigned long Solution::number_of_move_ops = 1;
const unsigned long Solution::number_of_objectives = 1;
const std::string Solution::name = "Fluid Problem";
const long double Solution::goal = 0.1;

// Problem definition
const std::vector< std::vector<long double>> Solution::in_xyz = {{7, 8, 9}, {10, 11, 12}};
const std::vector< std::vector<long double>> Solution::out_xyz = {{1, 2, 3}, {4, 5, 6}};
const std::vector<long double> Solution::in_flow = {0.25, 0.15};
const std::vector<long double> Solution::out_flow = {0.25, 0.15};


Solution::Solution(void) {
    // Give the solution a unique ID and increment the counter
    solution_id = solution_counter;
    solution_counter++;

    // Create nodes at each of the specified locations
    for(int i=0; i < out_xyz.size(); i++) {
        add_junction(out_xyz[i][0], out_xyz[i][1], out_xyz[i][2]);
        nodes[node_id_counter].parameters["moveable"] = false;
    }
    for(int i=0; i < out_xyz.size(); i++) {
        add_junction(in_xyz[i][0], in_xyz[i][1], in_xyz[i][2]);
        nodes[node_id_counter].parameters["moveable"] = false;
    }

    // Initialize quality
    quality.assign(number_of_objectives, LDBL_MAX);
    compute_quality();
}

void Solution::compute_quality(void) {
    // For now, just sum the length
    quality[0] = 1000;
    for(int i=0; i<edges.size(); i++) {
        quality[0] -= edges[i].parameters["L"];
    }
}

void Solution::get_valid_moves(void) {
    std::vector<int> order;

    // Adding a node is always an option
    print("\n");
    move_options.push_back(std::vector<int> {0, 0, 0});

    // Pull valid edge addition moves
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        for (std::map<int, Node>::iterator it2 = nodes.begin(); it2 != nodes.end(); it2++) {
            if (!undirected_edge_exists((it1->first), (it2->first))) {
                if((it2->first) != (it1->first)) {
                    order = {1, (it1->first), (it2->first)};
                    print(order);
                    move_options.push_back(order);
                }
            }
        }
    }
    print("\n");
}

void Solution::apply_move_operator(int n) {
    int n1 = uniform_int(static_cast<int>(nodes.size()-1), 0);
    int n2 = uniform_int(static_cast<int>(nodes.size()-1), 0);
    add_pipe(n1, n2, 0.1, 0.1);

    // Compute the quality
    compute_quality();
}

void Solution::add_pipe(int n1, int n2, long double d1, long double d2) {
    // Add an edge
    add_edge(n1, n2);

    // Add parameters for the edges
    edges[edge_id_counter].parameters["d1"] = d1;
    edges[edge_id_counter].parameters["d2"] = d1;

    // Compute the length
    edges[edge_id_counter].parameters["L"] = euclidean_distance(n1, n2);
}

void Solution::add_junction(long double x, long double y, long double z) {
    // Add the node
    add_node();

    // Add the coordinates
    nodes[node_id_counter].parameters["x"] = x;
    nodes[node_id_counter].parameters["y"] = y;
    nodes[node_id_counter].parameters["z"] = z;
}

////////////////////////////////////////////
///////////// Need to complete /////////////
void Solution::add_junction(int e) {
    int n1 = edges[e].initial_node;
    int n2 = edges[e].terminal_node;
}
///////////// Need to complete /////////////
////////////////////////////////////////////

void Solution::print_surface_characteristics(void) {
    print("Problem Characteristics");
    std::cout << "\tName: " << name << std::endl;
    std::cout << "\tGoal: " << goal << std::endl;
    std::cout << "\tNumber of move operators: " << number_of_move_ops << std::endl;
}

void Solution::is_valid(void) {
    // Used breadth first search
}

long double Solution::euclidean_distance(int n1, int n2) {
    return std::sqrt(
                       std::pow(nodes[n1].parameters["x"] - nodes[n2].parameters["x"], 2)
                     + std::pow(nodes[n1].parameters["y"] - nodes[n2].parameters["y"], 2)
                     + std::pow(nodes[n1].parameters["z"] - nodes[n2].parameters["z"], 2)
    );
}