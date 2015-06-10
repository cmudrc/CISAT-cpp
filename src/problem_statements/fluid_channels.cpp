#include "../../include/problem_statements/fluid_channels.hpp"

// Integer to assign unique IDs to solutions
int Solution::solution_counter = 0;
const unsigned long Solution::number_of_move_ops = 5;
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
        add_junction(out_xyz[i][0], out_xyz[i][1], out_xyz[i][2], false);
    }
    for(int i=0; i < out_xyz.size(); i++) {
        add_junction(in_xyz[i][0], in_xyz[i][1], in_xyz[i][2], false);
    }

    // Add a node to the average position, and connect all edges
    long double sum_x=0, sum_y=0, sum_z=0;
    unsigned long n = nodes.size();
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        sum_x += nodes[it1->first].parameters["x"];
        sum_y += nodes[it1->first].parameters["y"];
        sum_z += nodes[it1->first].parameters["z"];
    }

    add_junction(sum_x/n, sum_y/n, sum_z/n, true);
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        if((it1->first) != node_id_counter) {
            add_edge(it1->first, node_id_counter);
        }
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
    move_options.clear();
    move_options.assign(5, std::vector< std::vector<int> > ());
    move_options[0].push_back(std::vector<int> {0, 0, 0});

    // Pull valid edge addition moves and node deletion moves
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        if(nodes[it1->first].parameters["moveable"] == true){
            order = {4, it1->first, 0};
            move_options[4].push_back(order);
        }
        for (std::map<int, Node>::iterator it2 = nodes.begin(); it2 != nodes.end(); it2++) {
            if (!undirected_edge_exists((it1->first), (it2->first))) {
                if((it2->first) != (it1->first)) {
                    order = {1, (it1->first), (it2->first)};
                    move_options[1].push_back(order);
                }
            }
        }
    }

    // Pull valid junction addition and edge deletion moves
    for (std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); it1++) {
        order = {2, it1->first, 0};
        move_options[2].push_back(order);
        order = {3, it1->first, 0};
        move_options[2].push_back(order);
    }
}


void Solution::apply_move_operator(int move_type, int move_number) {
    std::vector<int> selected_order = move_options[move_type][move_number];

    // Switch statement based on first part of order
    // 0  Add a junction somewhere in the space.
    // 1  Add a pipe between junctions order[1] and order[2]
    // 2  Add a junction on the edge order[1]
    switch(selected_order[0]) {
        case 0:
            // Create a junction by taking a random affine combination fo two nodes
            {
            long double r = uniform(1.0, 0.0);
            int n1 = uniform_int(static_cast<int> (nodes.size() - 1), 0);
            int n2 = uniform_int(static_cast<int> (nodes.size() - 1), 0);

            add_junction(
                    r * nodes[n1].parameters["x"] + (1 - r) * nodes[n2].parameters["x"],
                    r * nodes[n1].parameters["y"] + (1 - r) * nodes[n2].parameters["y"],
                    r * nodes[n1].parameters["z"] + (1 - r) * nodes[n2].parameters["z"],
                    false
            );
            }
            break;
        case 1:
            add_pipe(selected_order[1], selected_order[2], 0.1, 0.1);
            break;
        case 2:
            add_midpoint_junction(selected_order[1]);
            break;
        case 3:
            remove_pipe(selected_order[1]);
            break;
        case 4:
            remove_junction(selected_order[1]);
            break;
        default:
            break;
    }

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


void Solution::add_junction(long double x, long double y, long double z, bool moveable) {
    // Add the node
    add_node();

    // Add the coordinates
    nodes[node_id_counter].parameters["x"] = x;
    nodes[node_id_counter].parameters["y"] = y;
    nodes[node_id_counter].parameters["z"] = z;

    // Moveable or not
    nodes[node_id_counter].parameters["moveable"] = moveable;
}


void Solution::add_midpoint_junction(int e) {
    // Save the indices of the endpoints
    int n1 = edges[e].initial_node;
    int n2 = edges[e].terminal_node;

    // Remove the edge
    remove_pipe(e);

    // Add a new node
    add_junction(
            (nodes[n1].parameters["x"] + nodes[n2].parameters["x"])/2,
            (nodes[n1].parameters["y"] + nodes[n2].parameters["y"])/2,
            (nodes[n1].parameters["z"] + nodes[n2].parameters["z"])/2,
      false
    );

    // Add new edges
    add_pipe(n1, node_id_counter, 0.1, 0.1);
    add_pipe(n2, node_id_counter, 0.1, 0.1);
}


void Solution::remove_pipe(int e) {
    remove_edge(e);
}


void Solution::remove_junction(int n) {
    remove_node(n);
}


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