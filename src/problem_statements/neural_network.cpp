//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─neural_network.cpp

#if PROBLEM_STATEMENT == NEURAL
#include "../../include/problem_statements/neural_network.hpp"

// Graph grammar characteristics
#if RULE_SET == CAMPBELL
    const  unsigned long  Solution::number_of_move_ops   = 4;
#elif RULE_SET == MCCOMB
    const  unsigned long  Solution::number_of_move_ops   = 6;
#endif

const  unsigned long  Solution::number_of_objectives = 1;
const  std::vector<long double>    Solution::goal    = {0.0};

std::vector< std::map<std::string, long double> > Solution::seed_graph_parameters = {{}};

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

    // Make samples to use for training
    make_samples();

    // Initialize quality
    quality.assign(number_of_objectives, LDBL_MAX);
    compute_quality();
}


#if RULE_SET == CAMPBELL
void Solution::apply_move_operator(int rule_number){
    switch(rule_number) {
        case 0:
            r3_replace_with_noded_edge();
            break;
        case 1:
            r4_add_bypass();
            break;
        case 2:
            r5_add_parallel_edge();
            break;
        case 3:
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

#if RULE_SET == MCCOMB
void Solution::apply_move_operator(int rule_number){
    switch(rule_number) {
        case 0:
            r3_replace_with_noded_edge();
            break;
        case 1:
            r4_add_bypass();
            break;
        case 2:
            r5_add_parallel_edge();
            break;
        case 3:
            r6_add_hidden_node();
            break;
        case 4:
            remove_nn_edge();
            break;
        case 5:
            remove_nn_node();
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

void Solution::remove_nn_edge(void){
    // Define a few things
    std::vector<int> editable = get_edge_ids("editable", true);
    std::vector<long double> weights(editable.size(), 1.0);

    if(weights.size() > 0.0){
        // Select an edge to delete
        int idx = weighted_choice(weights);

        // Remove the edge
        remove_edge(editable[idx]);
    }
}

void Solution::remove_nn_node(void){
    // Define a few things
    std::vector<int> editable = get_node_ids("editable", true);
    std::vector<long double> weights(editable.size(), 1.0);

    if(weights.size() > 0.0){
        // Select an edge to delete
        int idx = weighted_choice(weights);

        // Remove the edge
        remove_node(editable[idx]);
    }
}

#endif


// Add a nn node
void Solution::add_nn_node(bool editable, int type, long double layer) {
    // Add teh node
    add_node();

    // Define attributes
    nodes[node_id_counter].parameters["type"] = type;
    nodes[node_id_counter].parameters["layer"] = layer;
    nodes[node_id_counter].parameters["editable"] = editable;
    nodes[node_id_counter].parameters["y"] = 0;
    nodes[node_id_counter].parameters["z"] = 0;
    edges[edge_id_counter].parameters["bias"] = 0.0;
    edges[edge_id_counter].parameters["value"] = -1.0;


    // Add the layer
    add_layer(layer);
}

// Add a nn edge
void Solution::add_nn_edge(int n1, int n2, bool editable){
    // Add the edge in the appropriate direction
    if(nodes[n2].parameters["layer"] > nodes[n1].parameters["layer"]){
        add_edge(n1, n2);
    } else {
        add_edge(n2, n1);
    }

    // Save edge as editable
    edges[edge_id_counter].parameters["editable"] = editable;
    edges[edge_id_counter].parameters["weight"] = 1.0;
}


void Solution::create_seed_graph(void){
    // Add an input
    add_nn_node(false, INPUT, 0.0);
    int n1 = node_id_counter;

    // Add an output
    add_nn_node(false, OUTPUT, 1.0);
    int n2 = node_id_counter;

    // Add a single hidden node
    add_nn_node(true, HIDDEN, 0.5);

    // Add edges
    add_nn_edge(n1, node_id_counter, true);
    add_nn_edge(node_id_counter, n2, true);
}


// Functions
void Solution::compute_quality(void){
    // Train the neural network
    train_nn();

    // Assign the quality
    quality[0] = compute_mse();
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
        add_nn_edge(list[idx][0], list[idx][1], true);
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
        add_nn_node(true, HIDDEN, (nodes[list[idx][0]].parameters["layer"]+nodes[list[idx][1]].parameters["layer"])/2);

        // Connect the edges
        add_nn_edge(node_id_counter, list[idx][1], true);
        add_nn_edge(node_id_counter, list[idx][0], true);
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
        add_nn_node(true, HIDDEN, (nodes[n1].parameters["layer"]+nodes[n2].parameters["layer"])/2);

        // Add edges back
        add_nn_edge(node_id_counter, n1, true);
        add_nn_edge(node_id_counter, n2, true);
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
        add_nn_edge(list[idx][0], list[idx][1], true);
    }
}


// This function...
void Solution::r5_add_parallel_edge(void){
    r1_connect_with_edge();
}


// This function...
void Solution::r6_add_hidden_node(void){
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
                for(int i=0; i<common.size(); i++) {
                    if(std::abs(nodes[common[i]].parameters["layer"]) != 1.0) {
                        list.push_back({common[i], n1, n2});
                        weights.push_back(1.0);
                    }
                }
            }
        }
    }

    if (weights.size() > 0) {
        // Select an option adn implement it
        int idx = weighted_choice(weights);


        // Add a node
        add_nn_node(true, HIDDEN, nodes[list[idx][0]].parameters["layer"]);

        // Connect the node
        add_nn_edge(node_id_counter, list[idx][1], true);
        add_nn_edge(node_id_counter, list[idx][2], true);
    }

}


// Computes an output value given inputs
std::vector<long double> Solution::compute_nn_value(std::vector<long double> inputs){
    // Set input values at input nodes
    std::vector<int> node_ids = get_node_ids("type", INPUT);

    // Set input value
    for(int i=0; i<node_ids.size(); i++){
        nodes[node_ids[i]].parameters["value"] = inputs[i];
    }

    // Step through layers to update, starting at the first hidden layer
    for(int i=1; i<layers.size(); i++){
        // Find out which nodes are in the layer
        node_ids = get_node_ids("layer", layers[i]);

        // Compute the value for each
        for(int j=0; j<node_ids.size(); j++){
            // Initialize value to bias term
            nodes[node_ids[j]].parameters["value"] = nodes[node_ids[j]].parameters["bias"];

            // For every incoming edge, get the value
            for(int k=0; k<nodes[node_ids[j]].incoming_edges.size(); k++){
                int e = nodes[node_ids[j]].incoming_edges[k];
                int n = edges[e].initial_node;
                nodes[node_ids[j]].parameters["value"] += nodes[n].parameters["value"]*edges[e].parameters["weight"];
            }
            nodes[node_ids[j]].parameters["value"] = logistic_sigmoid(nodes[node_ids[j]].parameters["value"] );
        }
    }

    // Pull the output values
    node_ids = get_node_ids("type", OUTPUT);

    // Set input value
    std::vector<long double> outputs(node_ids.size(), 0.0);
    for(int i=0; i<node_ids.size(); i++){
        outputs[i] = nodes[node_ids[i]].parameters["value"];
    }

    // Return the data
    return outputs;
}


void Solution::make_samples(void){
    number_of_samples = 100;
    x_sample.assign(static_cast<unsigned long> (number_of_samples), std::vector<long double> (1, 0.0));
    y_sample.assign(static_cast<unsigned long> (number_of_samples), std::vector<long double> (1, 0.0));
    for(int i=0; i<100; i++){
        x_sample[i][0] = i/20;
        y_sample[i][0] = std::sin(x_sample[i][0]) + uniform(0.05, 0.05);
    }
}


long double Solution::compute_mse(void){
    // Initialize a thing
    long double mse = 0;

    // Sum the mse for each sample
    std::vector<long double> y_est;
    for(int i=0; i<y_sample.size(); i++) {
        y_est = compute_nn_value(x_sample[i]);
        for (int j=0; j< y_est.size(); j++){
            mse += std::pow(y_sample[i][j] - y_est[j], 2);
        }
    }

    mse /= (y_est.size() * number_of_samples);

    // Return a thing
    return mse;
}


// This function trains the neural network
void Solution::train_nn(void) {

}

// Determines if the network is valid
// TODO: Update so this returns true if connected
bool Solution::is_valid(void) {
    return true;
}


// Saves in an x3d format
void Solution::save_as_x3d(std::string save_to_file){
    WriteX3D x3d;
    int n1, n2;

    // Open the file
    x3d.open_file(save_to_file);

    // Give values to y
    std::vector<int> nodes_in_layer;
    unsigned long nn;
    for(int i=0; i<layers.size(); i++){
        // Find teh nodes
        nodes_in_layer = get_node_ids("layer", layers[i]);

        // Figure out how many there are
        nn = nodes_in_layer.size();

        // Give them value
        for(int j=0; j<nn; j++){
            nodes[nodes_in_layer[j]].parameters["y"] = -0.5 + (j+1.0)/(nn+1.0);
            nodes[nodes_in_layer[j]].parameters["z"] = uniform(0.10, -0.10);
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
    std::sort(layers.begin(), layers.end());
}


#endif