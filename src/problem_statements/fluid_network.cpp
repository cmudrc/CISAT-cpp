//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─fluid_network.cpp

#include "../../include/problem_statements/fluid_network.hpp"

// Graph grammar characteristics
const  unsigned long  Solution::number_of_move_ops   = 7;
const  unsigned long  Solution::number_of_objectives = 1;
const  std::string    Solution::name                 = "Gravity Fed Fluid Network";
const  long double    Solution::goal                 = 0.0;

// Fluid constants
const  long double    Solution::fluid_u              = 1.3*std::pow(10,-3); // [PA-s]

//Available pipe sizes
const std::vector< long double > Solution::pipe_diam = {0.02, 0.04, 0.06, 0.08, 0.10};

enum NodeTypes {INLET=1, INTERMEDIATE, OUTLET};

// Problem definition
std::vector< std::map<std::string, long double> > Solution::seed_graph_parameters = {
    {
        {"x",      0.00}, // [m]
        {"y",      0.00}, // [m]
        {"z",      0.00}, // [m]
        {"p",  35000.00}, // [Pa]
        {"type", INLET}
    }, {
        {"x",  5.00},
        {"y",  0.00},
        {"z",  0.00},
        {"p", 35000.00}, // [Pa]
        {"type", INLET}
    }, {
        {"x",  0.00},
        {"y",  25.00},
        {"z",  0.00},
        {"p", -1.00}, // [Pa]
        {"type", OUTLET}
    }, {
        {"x",  5.00},
        {"y", 25.00},
        {"z",  0.00},
        {"p", -1.00}, // [Pa]
        {"type", OUTLET}
    }
};


// Integer to assign unique IDs to solutions
int Solution::solution_counter = 0;


// Null constructor
Solution::Solution(void) {}


// A real constructor
Solution::Solution(bool) {
    // Give the solution a unique ID and increment the counter
    solution_id = solution_counter;
    solution_counter++;

    // Create seed graph
    create_seed_graph();

    // Initialize quality
    quality.assign(number_of_objectives, LDBL_MAX);
    compute_quality();
}


void Solution::create_seed_graph(void) {
    // Create nodes at each of the specified locations
    for(int i=0; i < seed_graph_parameters.size(); i++) {
        add_junction(seed_graph_parameters[i]["x"],
                     seed_graph_parameters[i]["y"],
                     seed_graph_parameters[i]["z"],
                     false);


        nodes[node_id_counter].parameters["type"] = INTERMEDIATE;
        if(seed_graph_parameters[i]["type"] == INLET) {
            add_junction(seed_graph_parameters[i]["x"],
                         seed_graph_parameters[i]["y"],
                         seed_graph_parameters[i]["z"]+0.1,
                         false);
            nodes[node_id_counter].parameters["type"] = seed_graph_parameters[i]["type"];
            nodes[node_id_counter].parameters["p"] = seed_graph_parameters[i]["p"];
        } else {
            add_junction(seed_graph_parameters[i]["x"],
                         seed_graph_parameters[i]["y"],
                         seed_graph_parameters[i]["z"]-0.1,
                         false);
            nodes[node_id_counter].parameters["type"] = seed_graph_parameters[i]["type"];
            nodes[node_id_counter].parameters["p"] = seed_graph_parameters[i]["p"];
        }
        add_pipe(node_id_counter, node_id_counter-1, 0, false);
    }

    // Create a central junction
    double cx=0, cy=0, cz=0;
    for(int i=0; i<seed_graph_parameters.size(); i++) {
        cx += seed_graph_parameters[i]["x"];
        cy += seed_graph_parameters[i]["y"];
        cz += seed_graph_parameters[i]["z"];
    }
    cx /= seed_graph_parameters.size();
    cy /= seed_graph_parameters.size();
    cz /= seed_graph_parameters.size();
    add_junction(cx, cy, cz, true);

    // Connect the central junction to all intermediate nodes
    int k;
    for(std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        k = (it->first);
        if(nodes[k].parameters["type"] == INTERMEDIATE && k != node_id_counter){
            add_pipe(k, node_id_counter, 0, true);
        }
    }
}


void Solution::compute_quality(void) {

    // Define the global stiffness matrix
    std::vector< std::vector<long double> > k_global(static_cast<unsigned long>(number_of_nodes), std::vector<long double>(static_cast<unsigned long>(number_of_nodes+1), 0.0));

    // Get the vector that will relate entries in the node map to entries in the global stiffness matrix
    std::map<int, int> node_id_map;
    int counter = 0;
    for(std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        node_id_map[(it->first)] = counter;
        counter++;
    }

    // For every existing element, add to the global matrix
    int k;
    int idx1 = 0;
    int idx2 = 0;
    for (std::map<int, Edge>::iterator it=edges.begin(); it!=edges.end(); it++) {
        k = (it->first);
        idx1 = node_id_map[edges[k].initial_node];
        idx2 = node_id_map[edges[k].terminal_node];
        edges[k].parameters["R"] = M_PI*std::pow(pipe_diam[edges[k].parameters["D"]], 4)/(128.0*edges[k].parameters["L"]*fluid_u);
        k_global[idx1][idx1] += edges[k].parameters["R"];
        k_global[idx1][idx2] -= edges[k].parameters["R"];
        k_global[idx2][idx1] -= edges[k].parameters["R"];
        k_global[idx2][idx2] += edges[k].parameters["R"];
    }

    // Add boundary conditions for each inlet and outlet, make pressure vector
    for(std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        k = (it->first);
        idx1 = node_id_map[k];
        if(nodes[k].parameters["type"] == INLET || nodes[k].parameters["type"] == OUTLET) {
            for (int i = 0; i < k_global[idx1].size(); i++) {
                k_global[idx1][i] = 0.0;
            }
            k_global[idx1][idx1] = 1.0;
            k_global[idx1][number_of_nodes] = nodes[k].parameters["p"];
        }
    }

    // Solve the matrix and find the elemental flow rates
    std::vector<long double> p = gauss(k_global);
    long double total_length = 0;
    for (std::map<int, Edge>::iterator it=edges.begin(); it!=edges.end(); it++) {
        k = (it->first);
        idx1 = node_id_map[edges[k].initial_node];
        idx2 = node_id_map[edges[k].terminal_node];
        edges[k].parameters["Q"] = edges[k].parameters["R"]*(p[idx1] - p[idx2]);
        total_length += edges[k].parameters["L"];
    }

    quality[0] = 0;
    for(int i=2; i<4; i++) {
        print(edges[i].parameters["Q"]);
//        quality[0] += 10000000*std::pow((0.001 + edges[i].parameters["Q"]), 2);
        quality[0] += 10000000*std::abs((0.001 + edges[i].parameters["Q"]));
    }
//    quality[0] += 100000*is_valid();
    quality[0] += 10000*is_valid() + total_length*10 + 100*number_of_nodes;

}


void Solution::apply_move_operator(int move_type) {
    switch(move_type) {
        case 0:
            add_pipe();
            break;
        case 1:
            add_midpoint_junction();
            break;
        case 2:
            remove_pipe();
            break;
        case 3:
            remove_junction();
            break;
        case 4:
            increase_pipe_size();
            break;
        case 5:
            decrease_pipe_size();
            break;
        case 6:
            move_junction();
            break;
        default:
            break;
    }

    // Compute the quality
    compute_quality();

    // asdf
    solution_counter++;
    solution_id++;
}


void Solution::add_pipe(int n1, int n2, int d, bool editable) {
    // Add an edge
    add_edge(n1, n2);

    // Add parameters for the edges
    edges[edge_id_counter].parameters["editable"] = editable;
    edges[edge_id_counter].parameters["D"] = d;
    edges[edge_id_counter].parameters["Q"] = 0.0;
    edges[edge_id_counter].parameters["p"] = 0.0;

    // Compute the length
    edges[edge_id_counter].parameters["L"] = euclidean_distance(n1, n2);
}

void Solution::add_pipe(void) {
    // Define a couple of things
    std::vector<int> editable = get_node_ids("type", INTERMEDIATE);
    std::vector<long double> weights(editable.size(), 1.0);

    // Select a pair to connect between at random
    int idx = weighted_choice(weights);
    int n1 = editable[idx];
    weights[idx] = 0.0;
    int n2 = editable[weighted_choice(weights)];

    // Add an edge
    add_pipe(n1, n2, 2, true);
}


void Solution::add_junction(long double x, long double y, long double z, bool editable) {
    // Add the node
    add_node();

    // Add the coordinates
    nodes[node_id_counter].parameters["x"] = x;
    nodes[node_id_counter].parameters["y"] = y;
    nodes[node_id_counter].parameters["z"] = z;

    // Moveable or not
    nodes[node_id_counter].parameters["editable"] = editable;
    nodes[node_id_counter].parameters["type"] = INTERMEDIATE;
}

// TODO: Update operators to keep a running list of editable edges
void Solution::remove_pipe(void) {
    // Define a couple of things
    std::vector<int> editable = get_edge_ids("editable", true);
    std::vector<long double> weights(editable.size(), 1.0);

    // Select one to remove at random
    int idx = weighted_choice(weights);

    // Remove the chosen edge
    remove_edge(editable[idx]);
}

// TODO: Update operators to keepa running list of editable nodes
void Solution::remove_junction(void) {
    // Define a couple of things
    std::vector<int> editable = get_node_ids("editable", true);
    std::vector<long double> weights(editable.size(), 1.0);


    // Select one to remove at random
    int idx = weighted_choice(weights);

    // Remove the specific node
    remove_node(editable[idx]);
}


void Solution::increase_pipe_size(void) {
    // Define a couple of things
    std::vector<int> editable = get_edge_ids("editable", true);
    std::vector<long double> weights(editable.size(), 1.0);

    // Select one to remove at random
    int idx = weighted_choice(weights);

    // Increase the size of the chosen edge
    edges[editable[idx]].parameters["d"]++;
}


void Solution::decrease_pipe_size(void) {
    // Define a couple of things
    std::vector<int> editable = get_edge_ids("editable", true);
    std::vector<long double> weights(editable.size(), 1.0);

    // Select one to remove at random
    int idx = weighted_choice(weights);

    // Decrease the size of the chosen edge
    edges[editable[idx]].parameters["d"]--;
}


void Solution::move_junction(void) {
    // Define a couple of things
    std::vector<int> editable = get_node_ids("editable", true);
    std::vector<long double> weights(editable.size(), 1.0);

    // Select one to move at random
    int idx = weighted_choice(weights);

    // Move it somehow TODO: Make this more intelligent
    nodes[editable[idx]].parameters["x"] += uniform(-1.0, 1.0);
    nodes[editable[idx]].parameters["y"] += uniform(-1.0, 1.0);
    nodes[editable[idx]].parameters["z"] += uniform(-1.0, 1.0);

    // Brute force length update TODO Avoid brute-forcedness
    for (std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); it1++) {
        edges[it1->first].parameters["L"] = euclidean_distance(edges[it1->first].initial_node, edges[it1->first].terminal_node);
    }
}


void Solution::add_midpoint_junction(void) {
    // Define a couple of things
    std::vector<int> editable = get_edge_ids("editable", true);
    std::vector<long double> weights(editable.size(), 1.0);

    // Select one to remove at random
    int idx = weighted_choice(weights);
    int e = editable[idx];

    // Save the indices of the endpoints
    int n1 = edges[e].initial_node;
    int n2 = edges[e].terminal_node;
    int d = static_cast <int> (edges[e].parameters["d"]);

    // Remove the edge
    remove_edge(e);

    // Add a new node
    add_junction(
            (nodes[n1].parameters["x"] + nodes[n2].parameters["x"])/2,
            (nodes[n1].parameters["y"] + nodes[n2].parameters["y"])/2,
            (nodes[n1].parameters["z"] + nodes[n2].parameters["z"])/2,
            false
    );

    // Add new edges
    add_pipe(n1, node_id_counter, d, true);
    add_pipe(n2, node_id_counter, d, true);
}


// Function to ensure that the solution is valid
int Solution::is_valid(void) {
    return is_connected();
}


void Solution::save_as_x3d(std::string save_to_file) {
    WriteX3D x3d;
    int n1, n2;

    x3d.open_file(save_to_file);
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        x3d.write_sphere(nodes[it1->first].parameters["x"], nodes[it1->first].parameters["y"], nodes[it1->first].parameters["z"], 1);
    }

    for (std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); it1++) {
        n1 = edges[it1->first].initial_node;
        n2 = edges[it1->first].terminal_node;
        x3d.write_line(nodes[n1].parameters["x"], nodes[n1].parameters["y"], nodes[n1].parameters["z"],
                       nodes[n2].parameters["x"], nodes[n2].parameters["y"], nodes[n2].parameters["z"],
                       edges[it1->first].parameters["d"]);
    }


    x3d.close_file();
}