//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─neural_network.cpp

#if PROBLEM_STATEMENT == NEURAL
#include "../../include/problem_statements/neural_network.hpp"

// Graph grammar characteristics
const  unsigned long  Solution::number_of_move_ops   = 6;
const  unsigned long  Solution::number_of_objectives = 1;
const  long double    Solution::goal                 = 0.0;

std::vector< std::map<std::string, long double> > Solution::seed_graph_parameters = {
        {}
};

// Integer to assign unique IDs to solutions
int Solution::solution_counter = 0;

enum NodeTypes {INPUT=-1, HIDDEN, OUTPUT};

// Null constructor
Solution::Solution(void){}


Solution::Solution(bool){
    // Give the solution a unique ID and increment the counter
    solution_id = solution_counter;
    solution_counter++;

    // Create seed graph
    create_seed_graph();

    // Initialize quality
    quality.assign(number_of_objectives, LDBL_MAX);
    compute_quality();
}


#if RULE_SET == CAMPBELL
void Solution::apply_move_operator(int rule_number){
    switch(rule_number) {
        case 0:
            r1_connect_with_edge();
            break;
        case 1:
            r2_connect_with_noded_edge();
            break;
        case 2:
            r3_replace_with_noded_edge();
            break;
        case 3:
            r4_add_bypass();
            break;
        case 4:
            r5_add_parallel_edge();
            break;
        case 5:
            r6_add_hidden_node();
            break;
        default:
            break;
    }

    // Compute the quality
    compute_quality();

    // Increment solution counters and things?
    solution_counter++;
    solution_id++;
}
#endif

// Functions
void Solution::compute_quality(void){
    quality[0] = uniform(10.0, 0.0);
}


void Solution::create_seed_graph(void){
    // Add an inlet
    add_node();
    nodes[node_id_counter].parameters["type"] = INPUT;
    nodes[node_id_counter].parameters["layer"] = -1;
    nodes[node_id_counter].parameters["editable"] = false;
    nodes[node_id_counter].parameters["y"] = 0;
    nodes[node_id_counter].parameters["z"] = 0;
    layers.push_back(-1);

    // Add an outlet
    add_node();
    nodes[node_id_counter].parameters["type"] = OUTPUT;
    nodes[node_id_counter].parameters["layer"] = +1;
    nodes[node_id_counter].parameters["editable"] = false;
    nodes[node_id_counter].parameters["y"] = 0;
    nodes[node_id_counter].parameters["z"] = 0;
    layers.push_back(+1);
}

// This function connects two nodes with an edge
void Solution::r1_connect_with_edge(void){
    // First define some things
    std::vector<long double> weights;
    std::vector<std::vector<int> > list;

    // Find all eligible node combinations
    for(std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1){
        for(std::map<int, Node>::iterator it2 = std::next(it1, 1); it2 != nodes.end(); ++it2) {
            int n1 = it1->first;
            int n2 = it2->first;
            if(!undirected_edge_exists(n1, n1) && nodes[n1].parameters["layer"]!=nodes[n2].parameters["layer"]) {
                list.push_back({n1, n2});
                weights.push_back(1.0);
            }
        }
    }

    // Select which node pair to implement
    if(weights.size() > 0) {
        int idx = weighted_choice(weights);
        add_edge(list[idx][0], list[idx][1]);
        edges[edge_id_counter].parameters["editable"] = true;
    }
}


// Connects two unconnected nodes with a noded edge
void Solution::r2_connect_with_noded_edge(void){
    // First define some things
    std::vector<long double> weights;
    std::vector<std::vector<int> > list;

    // Find all eligible node combinations. A combination is eligible if an edge doesnt already exist, and if nodes aren't in teh same layer
    for(std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1){
        for(std::map<int, Node>::iterator it2 = std::next(it1, 1); it2 != nodes.end(); ++it2) {
            int n1 = it1->first;
            int n2 = it2->first;
            if(!undirected_edge_exists(n1, n1) && nodes[n1].parameters["layer"]!=nodes[n2].parameters["layer"]) {
                list.push_back({n1, n2});
                weights.push_back(1.0);
            }
        }
    }

    if(weights.size() > 0) {
        // Select which node pair to implement
        int idx = weighted_choice(weights);

        // Add a node to go between
        add_node();
        nodes[node_id_counter].parameters["type"] = HIDDEN;
        nodes[node_id_counter].parameters["layer"] = (nodes[list[idx][0]].parameters["layer"]+nodes[list[idx][1]].parameters["layer"])/2;
        add_layer(nodes[node_id_counter].parameters["layer"]);
        nodes[node_id_counter].parameters["editable"] = true;
        nodes[node_id_counter].parameters["y"] = 0;
        nodes[node_id_counter].parameters["z"] = uniform(0.25, -0.25);

        // Connect the edges
        add_edge(node_id_counter, list[idx][1]);
        edges[edge_id_counter].parameters["editable"] = true;
        add_edge(node_id_counter, list[idx][0]);
        edges[edge_id_counter].parameters["editable"] = true;
    }
}


// This function replaces an existing edge with two edges and a node
void Solution::r3_replace_with_noded_edge(void){
    // First define some things
    std::vector<long double> weights;
    std::vector<int> list;

    // Every edges is available for this operation
    list = get_edge_ids("editable", true);
    weights.assign(list.size(), 1.0);

    if(weights.size() > 0){
        // Select an edge to operate on
        int idx = weighted_choice(weights);

        // Get the endpoints
        int n1 = edges[list[idx]].initial_node;
        int n2 = edges[list[idx]].terminal_node;

        // Remove the edge
        remove_edge(list[idx]);

        // Add a node, and add edges
        add_node();
        nodes[node_id_counter].parameters["type"] = HIDDEN;
        nodes[node_id_counter].parameters["layer"] = (nodes[n1].parameters["layer"]+nodes[n2].parameters["layer"])/2;
        add_layer(nodes[node_id_counter].parameters["layer"]);
        nodes[node_id_counter].parameters["y"] = (nodes[n1].parameters["y"]+nodes[n2].parameters["y"])/2;
        nodes[node_id_counter].parameters["editable"] = true;
        nodes[node_id_counter].parameters["z"] = uniform(0.25, -0.25);

        // Add edges back
        add_edge(node_id_counter, n1);
        edges[edge_id_counter].parameters["editable"] = true;
        add_edge(node_id_counter, n2);
        edges[edge_id_counter].parameters["editable"] = true;
    }
}


// This function...
void Solution::r4_add_bypass(void) {
    // First define some things
    std::vector<long double> weights;
    std::vector<std::vector<int> > list;

    // Find all eligible node combinations. A combination is eligible if an edge doesnt already exist, and if nodes aren't in teh same layer
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
        for (std::map<int, Node>::iterator it2 = std::next(it1, 1); it2 != nodes.end(); ++it2) {
            // Pull node numbers
            int n1 = it1->first;
            int n2 = it2->first;

            // Make sure we're not dealing with nodes in teh same layer.
            if (nodes[n1].parameters["layer"] != nodes[n2].parameters["layer"]) {
                // Find out if nodes have any neighbors
                std::vector<int> common = find_common_neighbors(n1, n2);

                // If the nodes have a common neighbor, save them as an option.
                if (common.size() > 0) {
                    list.push_back({n1, n2});
                    weights.push_back(1.0);
                }
            }
        }
    }

    // Select an option adn implement it
    if (weights.size() > 0) {
        int idx = weighted_choice(weights);
        add_edge(list[idx][0], list[idx][1]);
    }
}


// This function...
void Solution::r5_add_parallel_edge(void){
    //TODO: Write function for Rule #5
}


// This function...
void Solution::r6_add_hidden_node(void){
    //TODO: Write function for Rule #6
}



bool Solution::is_valid(void){
    return true;
}

//
void Solution::save_as_x3d(std::string save_to_file){
    WriteX3D x3d;
    int n1, n2;

    // Open the file
    x3d.open_file(save_to_file);

    // Give values to y
    std::vector<int> nodes_in_layer;
    int nn;
    for(int i=0; i<layers.size(); i++){
        // Find teh nodes
        nodes_in_layer = get_node_ids("layer", layers[i]);

        // Figure out how many there are
        nn = nodes_in_layer.size();

        // Give them value
        for(int j=0; j<nn; j++){
            nodes[nodes_in_layer[j]].parameters["y"] = -0.5 + static_cast<long double> (j+1)/(nn+1);
            nodes[nodes_in_layer[j]].parameters["z"] = 0;
        }
    }

    x3d.start_scene(0, 0, 3);
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        x3d.write_sphere(nodes[it1->first].parameters["layer"], nodes[it1->first].parameters["y"], nodes[it1->first].parameters["z"], 0.05);
    }

    for (std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); it1++) {
        n1 = edges[it1->first].initial_node;
        n2 = edges[it1->first].terminal_node;
        x3d.write_line(nodes[n1].parameters["layer"], nodes[n1].parameters["y"], nodes[n1].parameters["z"],
                       nodes[n2].parameters["layer"], nodes[n2].parameters["y"], nodes[n2].parameters["z"], 2);
    }

    x3d.close_scene();
    x3d.close_file();
}

void Solution::add_layer(long double L){
    if(std::find(layers.begin(), layers.end(), L) == layers.end()) {
        layers.push_back(L);
    }
}


#endif