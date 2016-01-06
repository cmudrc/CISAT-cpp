//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─fluid_network.cpp

#if PROBLEM_STATEMENT == FLUID
#include "../../include/problem_statements/fluid_network.hpp"

// Graph grammar characteristics
const  unsigned long  Solution::number_of_move_ops   = 6;
const  unsigned long  Solution::number_of_objectives = 2;

// Fluid constants
enum NodeTypes {INLET=1, INTERMEDIATE_INLET, OUTLET, INTERMEDIATE_OUTLET};

// Problem definition

#if PROBLEM_NUMBER == 0
    const  std::vector<long double>    Solution::goal                 = {-0.005, 400};
    const  long double    Solution::fluid_u              = 1.3*std::pow(10,-3); // [PA-s]
    //Available pipe sizes
    const std::vector< long double > Solution::pipe_diam = {0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14};
    std::vector< std::map<std::string, long double> > Solution::seed_node_parameters = {
        {{"set", 1}, {"x", 50.00}, {"y", 0.00}, {"z", 0.00}, {"p", 35000.00}, {"type", INLET}},
        {{"set", 1}, {"x", 75.00}, {"y", 20.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 100.00}, {"y", 40.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 100.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 100.00}, {"y", 60.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 80.00}, {"y", 80.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_OUTLET}},
        {{"set", 1}, {"x", 60.00}, {"y", 100.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 50.00}, {"y", 100.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 40.00}, {"y", 100.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 20.00}, {"y", 80.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_OUTLET}},
        {{"set", 1}, {"x", 0.00}, {"y", 60.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 0.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 0.00}, {"y", 40.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 25.00}, {"y", 20.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},

        {{"set", 1}, {"x", 50.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 25.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 75.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 50.00}, {"y", 25.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 50.00}, {"y", 75.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}}
    };

#elif PROBLEM_NUMBER == 1
    const  std::vector<long double>    Solution::goal                 = {-0.005, 400};
    const  long double    Solution::fluid_u              = 1.3*std::pow(10,-3); // [PA-s]
    const std::vector< long double > Solution::pipe_diam = {0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14};

    std::vector< std::map<std::string, long double> > Solution::seed_node_parameters = {
        {{"set", 1}, {"x", 50.00}, {"y", 50.00}, {"z", 0.00}, {"p", 35000.00}, {"type", INLET}},

        {{"set", 1}, {"x", 75.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 50.00}, {"y", 75.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 25.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 50.00}, {"y", 25.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},

        {{"set", 1}, {"x", 32.50}, {"y", 67.50}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 32.50}, {"y", 32.50}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 67.50}, {"y", 67.50}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 67.50}, {"y", 32.50}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},

        {{"set", 1}, {"x",   0.00}, {"y",  33.33}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x",   0.00}, {"y",  66.67}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 100.00}, {"y",  33.33}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 100.00}, {"y",  66.67}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x",  33.33}, {"y",   0.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x",  66.67}, {"y",   0.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x",  33.33}, {"y", 100.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x",  66.67}, {"y", 100.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}}
    };

#elif PROBLEM_NUMBER == 2
    const  std::vector<long double>    Solution::goal                 = {-0.005, 400};
    const  long double    Solution::fluid_u              = 0.3; // [PA-s]
    const std::vector< long double > Solution::pipe_diam = {0.04, 0.08, 0.12, 0.16, 0.20, 0.24, 0.28};
    std::vector< std::map<std::string, long double> > Solution::seed_node_parameters = {
        {{"set", 1}, {"x", 50.00}, {"y", 0.00}, {"z", 0.00}, {"p", 500000.00}, {"type", INLET}},
        {{"set", 1}, {"x", 75.00}, {"y", 20.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 100.00}, {"y", 40.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 100.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 100.00}, {"y", 60.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 80.00}, {"y", 80.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_OUTLET}},
        {{"set", 1}, {"x", 60.00}, {"y", 100.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 50.00}, {"y", 100.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 40.00}, {"y", 100.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 20.00}, {"y", 80.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_OUTLET}},
        {{"set", 1}, {"x", 0.00}, {"y", 60.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 0.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 0.00}, {"y", 40.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 25.00}, {"y", 20.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},

        {{"set", 1}, {"x", 50.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 25.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 75.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 50.00}, {"y", 25.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 50.00}, {"y", 75.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}}
    };


#elif PROBLEM_NUMBER == 3
    const  std::vector<long double>    Solution::goal                 = {-0.005, 400};
    const  long double    Solution::fluid_u              = 0.3; // [PA-s]
    const std::vector< long double > Solution::pipe_diam = {0.04, 0.08, 0.12, 0.16, 0.20, 0.24, 0.28};
    std::vector< std::map<std::string, long double> > Solution::seed_node_parameters = {
        {{"set", 1}, {"x", 50.00}, {"y", 50.00}, {"z", 0.00}, {"p", 500000.00}, {"type", INLET}},

        {{"set", 1}, {"x", 75.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 50.00}, {"y", 75.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 25.00}, {"y", 50.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 50.00}, {"y", 25.00}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},

        {{"set", 1}, {"x", 32.50}, {"y", 67.50}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 32.50}, {"y", 32.50}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 67.50}, {"y", 67.50}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},
        {{"set", 1}, {"x", 67.50}, {"y", 32.50}, {"z", 0.00}, {"p", -1.0}, {"type", INTERMEDIATE_INLET}},

        {{"set", 1}, {"x",   0.00}, {"y",  33.33}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x",   0.00}, {"y",  66.67}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 100.00}, {"y",  33.33}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x", 100.00}, {"y",  66.67}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x",  33.33}, {"y",   0.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x",  66.67}, {"y",   0.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x",  33.33}, {"y", 100.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}},
        {{"set", 1}, {"x",  66.67}, {"y", 100.00}, {"z", 0.00}, {"p", -1.0}, {"type", OUTLET}}
    };
#endif
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
    for(int i=0; i < seed_node_parameters.size(); i++) {

        // If its an inlet or outlet, add a node pair
        if(seed_node_parameters[i]["type"] == INLET || seed_node_parameters[i]["type"] == OUTLET) {
            add_junction(seed_node_parameters[i]["x"],
                         seed_node_parameters[i]["y"],
                         seed_node_parameters[i]["z"],
                         false);
            nodes[node_id_counter].parameters["type"] = seed_node_parameters[i]["type"]+1;


            add_junction(seed_node_parameters[i]["x"],
                         seed_node_parameters[i]["y"],
                         seed_node_parameters[i]["z"]+1.0,
                         false);
            nodes[node_id_counter].parameters["type"] = seed_node_parameters[i]["type"];
            nodes[node_id_counter].parameters["p"] = seed_node_parameters[i]["p"];
            add_pipe(node_id_counter, node_id_counter-1, 0, false);
        }
        // Else just add the node
        else {

            add_junction(seed_node_parameters[i]["x"] + uniform(10, -10),
                         seed_node_parameters[i]["y"] + uniform(10, -10),
                         seed_node_parameters[i]["z"],
                         true);
            nodes[node_id_counter].parameters["type"] = seed_node_parameters[i]["type"];
        }
    }

    // Connect all nodes probabilitisticaly
    std::vector<int> editable;
    std::vector<int> editable1 = get_node_ids("type", INTERMEDIATE_INLET);
    std::vector<int> editable2 = get_node_ids("type", INTERMEDIATE_OUTLET);
    editable.reserve( editable1.size() + editable2.size() ); // preallocate memory
    editable.insert( editable.end(), editable1.begin(), editable1.end() );
    editable.insert( editable.end(), editable2.begin(), editable2.end() );

    for(int i=0; i<editable.size(); i++){
        for(int j=i+1; j<editable.size(); j++){
            if(uniform(75.0, 0.0) < 75-euclidean_distance(editable[i], editable[j])){
                add_pipe(editable[i], editable[j], 2, true);
            }
        }
    }

}

void Solution::compute_quality(void) {
    // Define a few things
    int k;
    std::vector<long double> q;
    quality.assign(number_of_objectives, 0.0);

    // Solve it all
    compute_fluid_solution();

    // Extract the necessary flowrates
    std::vector<int> outlets = get_node_ids("type", OUTLET);
    for(int i=0; i<outlets.size(); i++){
        k = nodes[outlets[i]].outgoing_edges[0];
        q.push_back(std::abs(edges[k].parameters["Q"]));
    }
    print(q);

    // Now, compute qualities
    if(is_valid()) {

        // Compute discrepancy of flow rates
        long double min_flow = vector_minimum(q);
        quality[0] = -min_flow/goal[0];
        if(min_flow < -goal[0]) {
            quality[0] = -10*std::log(-min_flow/goal[0]) + 1;
        } else {
            quality[0] = 2 - quality[0];
        }

        // Compute total length
        for (std::map<int, Edge>::iterator it=edges.begin(); it!=edges.end(); it++) {
            k = (it->first);
            quality[1] += edges[k].parameters["L"];
        }
        quality[1]/=goal[1];
   } else {
        for(int i=0; i<number_of_objectives; i++){
            quality[i] = 100;//*goal[i];
        }
    }

//    print(quality);
}

void Solution::compute_fluid_solution(void) {

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

    // Solve the matrix and compute the condition number
    std::vector<long double> p = gauss(k_global);

    // Push solution back into last column of and multiple
    std::vector<long double> known_pressures(static_cast<unsigned long> (number_of_nodes), 0.0);
    for(int i=0; i<number_of_nodes; i++){
        known_pressures[i] = k_global[i][number_of_nodes];
        k_global[i][number_of_nodes] = p[i];
    }
    std::vector<long double> backed_out_pressures = matrix_vector_mult(k_global);

    // Compute condition number
    cond = 0;
    for(int i=0; i<number_of_nodes; i++){
        cond += std::abs(known_pressures[i] - backed_out_pressures[i]);
    }

    // Find the elemental information
    for (std::map<int, Edge>::iterator it=edges.begin(); it!=edges.end(); it++) {
        k = (it->first);
        idx1 = node_id_map[edges[k].initial_node];
        idx2 = node_id_map[edges[k].terminal_node];
        edges[k].parameters["Q"] = edges[k].parameters["R"]*(p[idx1] - p[idx2]);
    }
}

#if RULE_SET == MCCOMB
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
            change_pipe_size();
            break;
        case 5:
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

#elif RULE_SET == CAMPBELL
void Solution::apply_move_operator(int move_type) {
    switch(move_type) {
        case 0:
            inlet_to_outlet();
            break;
        case 1:
            intermediate_inlet();
            break;
        case 2:
            intermediate_outlet();
            break;
        case 3:
            remove_pipe();
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
#endif


void Solution::add_pipe(int n1, int n2, int d, bool editable) {
    // Add an edge
    add_edge(n1, n2);

    // Add parameters for the edges
    edges[edge_id_counter].parameters["editable"] = editable;
    edges[edge_id_counter].parameters["D"] = d;
    edges[edge_id_counter].parameters["Q"] = 0.0;

    // Compute the length
    edges[edge_id_counter].parameters["L"] = euclidean_distance(n1, n2);
}


// Adds a pipe randomly between two junctions
void Solution::add_pipe(void) {
    // Define a couple of things
    std::vector<int> editable;
    std::vector<int> editable1 = get_node_ids("type", INTERMEDIATE_INLET);
    std::vector<int> editable2 = get_node_ids("type", INTERMEDIATE_OUTLET);
    editable.reserve( editable1.size() + editable2.size() ); // preallocate memory
    editable.insert( editable.end(), editable1.begin(), editable1.end() );
    editable.insert( editable.end(), editable2.begin(), editable2.end() );
    std::vector<long double> weights(editable1.size() + editable2.size(), 1.0);

    // Select a pair to connect between at random
    int counter = 0;
    while (counter < 5) {
        int idx = weighted_choice(weights);
        int n1 = editable[idx];
        weights[idx] = 0.0;
        int n2 = editable[weighted_choice(weights)];

        // Add an edge
        if(!undirected_edge_exists(n1, n2)){
            add_pipe(n1, n2, 2, true);
            counter = 1000;
        } else {
            counter++;
        }
    }
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
}


void Solution::remove_pipe(void) {
    // Define a couple of things
    std::vector<int> editable = get_edge_ids("editable", true);
    std::vector<long double> weights(editable.size(), 1.0);

    // Add weighting
    for (int i=0; i<editable.size(); i++){
        weights[i] = std::abs(edges[editable[i]].parameters["Q"]);
    }

    // Invert weighting
    long double the_max = vector_maximum(weights);
    for (int i=0; i<weights.size(); i++){
        weights[i] = the_max - weights[i];
    }

    if(editable.size() > 0){
        // Select one to remove at random
        int idx = weighted_choice(weights);

        // Remove the chosen edge
        remove_edge(editable[idx]);
    }

    // Clean up
    clean_dangly_bits();
}


void Solution::remove_junction(void) {
    // Define a couple of things
    std::vector<int> editable = get_node_ids("editable", true);
    std::vector<long double> weights(editable.size(), 0.0);
    int k;

    // Add weighting
    for (int i=0; i<editable.size(); i++){
        for(int j=0; j<nodes[editable[i]].incoming_edges.size(); j++) {
            k = nodes[editable[i]].incoming_edges[j];
            weights[i] += std::abs(edges[k].parameters["Q"]);
        }
        for(int j=0; j<nodes[editable[i]].outgoing_edges.size(); j++) {
            k = nodes[editable[i]].outgoing_edges[j];
            weights[i] += std::abs(edges[k].parameters["Q"]);
        }
    }

    // Invert weighting
    long double the_max = vector_maximum(weights);
    for (int i=0; i<weights.size(); i++){
        weights[i] = the_max - weights[i];
    }

    if(editable.size() > 0) {
        // Select one to remove at random
        int idx = weighted_choice(weights);

        // Remove the specific node
        remove_node(editable[idx]);
    }

    // Clean up
    clean_dangly_bits();
}

void Solution::change_pipe_size(void) {
    // Define a couple of things
    std::vector<int> editable = get_edge_ids("editable", true);
    std::vector<long double> weights(editable.size(), 1.0);

    // If quality is ok, try to decrease size. Else, increase
    if(weights.size() > 0){
        if(quality[0] < 1.0) {
            // Refine weights
            for(int i=0; i<editable.size(); i++){
                if(edges[editable[i]].parameters["d"] == 0) {
                    weights[i] = 0.0;
                }
            }

            // Select one to remove at random
            int idx = weighted_choice(weights);

            // Decrease the size of the chosen edge
            edges[editable[idx]].parameters["d"]--;
        } else {
            // Refine weights
            for(int i=0; i<editable.size(); i++){
                if(edges[editable[i]].parameters["Q"] < -goal[0] && edges[editable[i]].parameters["d"] < pipe_diam.size()-1){
                    weights[i] = -goal[0] - edges[editable[i]].parameters["Q"];
                } else {
                    weights[i] = 0.0;
                }
            }

            // Select one to remove at random
            int idx = weighted_choice(weights);

            if(edges[editable[idx]].parameters["d"] < pipe_diam.size()-1) {
                edges[editable[idx]].parameters["d"]++;
            }
        }
    }

}

// This is the function that moves a junction with some level of determinicity
void Solution::move_junction(void){
    // Define a couple of things
    std::vector<int> editable = get_node_ids("editable", true);
    if(editable.size() > 0){

        // Select one to move at random
        std::vector<long double> weights(editable.size(), 1.0);
        int key = editable[weighted_choice(weights)];

        // Move it somehow
        long double step_size = 2.0;
        int max_iter = 8;
        long double best_quality = quality[1];
        std::vector< std::vector< long double> > unit_direction = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for(int i=0; i<max_iter; i++){
            for(int j=0; j<4; j++){
                // Try a move in the j^th direction
                nodes[key].parameters["x"] += unit_direction[j][0]*step_size;
                nodes[key].parameters["y"] += unit_direction[j][1]*step_size;

                // Compute quality
                compute_quality();

                // If improved, keep and break. Else, reverse.
                if(quality[1] < best_quality) {
                    best_quality = quality[1];
                    break;
                } else {
                    nodes[key].parameters["x"] -= unit_direction[j][0]*step_size;
                    nodes[key].parameters["y"] -= unit_direction[j][1]*step_size;
                };

                // If j == 4 without improvement, halve step size
                if (j==4) {
                    step_size /= 2.0;
                }

                // If the step size gets too small, exit. Its good enough.
                if (step_size < 0.1) {
                    i = max_iter;
                }
            }
        }

        //Update length related properties for the node that we moved.
        for(int i=0; i < nodes[key].outgoing_edges.size(); i++){
            update_length(nodes[key].outgoing_edges[i]);
        }
        for(int i=0; i < nodes[key].incoming_edges.size(); i++){
            update_length(nodes[key].incoming_edges[i]);
        }
    }
}


// This functions adds a junction at the midpoint
void Solution::add_midpoint_junction(void) {
    // Define a couple of things
    std::vector<int> editable = get_edge_ids("editable", true);
    std::vector<long double> weights(editable.size(), 1.0);

    if(editable.size() > 0){
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
            true
        );

        // Add new edges
        add_pipe(n1, node_id_counter, d, true);
        add_pipe(n2, node_id_counter, d, true);
    }
}


void Solution::inlet_to_outlet(void){
    // Find out where the available inlets nad outlets are
    std::vector<int> inlets  = get_node_ids("type", INTERMEDIATE_INLET);
    std::vector<int> outlets = get_node_ids("type", INTERMEDIATE_OUTLET);
    std::vector<int> fixed_inlets  = get_node_ids("type", INLET);
    std::vector<int> fixed_outlets = get_node_ids("type", OUTLET);

    if(inlets.size()*outlets.size() > number_of_edges - fixed_inlets.size() - fixed_outlets.size()) {
        // Make weighting vectors to accomodate future weightings
        std::vector<long double> inlet_weights(inlets.size(), 1.0);
        std::vector<long double> outlet_weights(outlets.size(), 1.0);

        // Select an inlet and an outlet and connect it
        bool SUCCESS = false;
        int n1, n2;
        int iter_counter = 0;
        while (!SUCCESS) {
            // Pick two edges
            n1 = inlets[weighted_choice(inlet_weights)];
            n2 = outlets[weighted_choice(outlet_weights)];

            // See if the edges exist
            if (!undirected_edge_exists(n1, n2)) {
                SUCCESS = true;
                add_pipe(n1, n2, 2, true);
            }
            if (iter_counter > 10) {
                break;
            }
        }
    }
}


// This adds an intermediate inlet between two other inlets
void Solution::intermediate_inlet(void){
    // Find out where the inlets are
    std::vector<int> inlets  = get_node_ids("type", INTERMEDIATE_INLET);

    // Make a weighting vector for future use
    std::vector<long double> inlet_weights(inlets.size(), 1.0);

    // Select the inlet and outlet to use
    int n1 = weighted_choice(inlet_weights);
    inlet_weights[n1] = 0.0;
    int n2 = weighted_choice(inlet_weights);

    // Add a joint between them
    add_junction(
        (nodes[n1].parameters["x"] + nodes[n2].parameters["x"])/2,
        (nodes[n1].parameters["y"] + nodes[n2].parameters["y"])/2,
        (nodes[n1].parameters["z"] + nodes[n2].parameters["z"])/2,
        true
    );
    nodes[node_id_counter].parameters["type"] = INTERMEDIATE_INLET;

    // Add new edges
    add_pipe(inlets[n1], node_id_counter, 2, true);
    add_pipe(inlets[n2], node_id_counter, 2, true);
}


// This adds an intermediate outlet between two other outlets
void Solution::intermediate_outlet(void) {
    // Find out where the inlets are
    std::vector<int> outlets = get_node_ids("type", INTERMEDIATE_OUTLET);

    // Make a weighting vector for future use
    std::vector<long double> outlet_weights(outlets.size(), 1.0);

    // Select the inlet and outlet to use
    int n1 = weighted_choice(outlet_weights);
    outlet_weights[n1] = 0.0;
    int n2 = weighted_choice(outlet_weights);

    // Add a joint between them
    add_junction(
        (nodes[n1].parameters["x"] + nodes[n2].parameters["x"]) / 2,
        (nodes[n1].parameters["y"] + nodes[n2].parameters["y"]) / 2,
        (nodes[n1].parameters["z"] + nodes[n2].parameters["z"]) / 2,
        true
    );
    nodes[node_id_counter].parameters["type"] = INTERMEDIATE_OUTLET;

    // Add new edges
    add_pipe(outlets[n1], node_id_counter, 2, true);
    add_pipe(outlets[n2], node_id_counter, 2, true);
}

// Function to ensure that the solution is valid
int Solution::is_valid(void) {
    // Define some things
    bool ALL_CONNECTED = true;
    bool GOOD_COND = true;
    int k;

    // Check the flow out of every outlet
    std::vector<int> outlets = get_node_ids("type", OUTLET);
    for(int i=0; i<outlets.size(); i++){
        k = nodes[outlets[i]].outgoing_edges[0];
        if(std::abs(edges[k].parameters["Q"]) > std::pow(10, -10)) {
            // Do nothing. The comparison needs to be this way to handle nans
        } else {
            ALL_CONNECTED = false;

        }
    }

    // Check the condition number
    if(cond > std::pow(10, -10)){
        GOOD_COND = false;
    }

    return ALL_CONNECTED && GOOD_COND;
}


void Solution::save_as_x3d(std::string save_to_file) {
    WriteX3D x3d;
    int n1, n2;

    x3d.open_file(save_to_file);
    #if PROBLEM_NUMBER == 0
        x3d.start_scene(50, 50, 125);
    #elif PROBLEM_NUMBER == 1
        x3d.start_scene(50, 50, 125);
    #elif PROBLEM_NUMBER == 2
        x3d.start_scene(50, 50, 125);
    #elif PROBLEM_NUMBER == 3
        x3d.start_scene(50, 50, 125);
    #endif
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        x3d.write_sphere(nodes[it1->first].parameters["x"], nodes[it1->first].parameters["y"], nodes[it1->first].parameters["z"], 0.5);
    }

    for (std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); it1++) {
        n1 = edges[it1->first].initial_node;
        n2 = edges[it1->first].terminal_node;
        x3d.write_line(nodes[n1].parameters["x"], nodes[n1].parameters["y"], nodes[n1].parameters["z"],
                       nodes[n2].parameters["x"], nodes[n2].parameters["y"], nodes[n2].parameters["z"],
                       static_cast<int> (edges[it1->first].parameters["d"]));
    }

    x3d.close_scene();
    x3d.close_file();
}

void Solution::update_length(int e){
    // Update the length
    edges[e].parameters["L"] = euclidean_distance(edges[e].initial_node, edges[e].terminal_node);
}

void Solution::clean_dangly_bits(void) {
//    // Update the quality
//    compute_quality();
//
//    // Remove edges that have 0 flow rate
//    std::vector<int> edges_to_remove;
//    for(std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); it1++){
//        if((std::abs(edges[it1->first].parameters["Q"]) < std::pow(10, -10))
//           && edges[it1->first].parameters["editable"]){
//            edges_to_remove.push_back(it1->first);
//        }
//    }
//    for(int i=0; i<edges_to_remove.size(); i++){
//        remove_edge(edges_to_remove[i]);
//    }
//
//    // Remove nodes that have no connections
//    std::vector<int> nodes_to_remove;
//    for(std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++){
//        if(((nodes[it1->first].incoming_edges.size() + nodes[it1->first].outgoing_edges.size()) == 0)
//           && nodes[it1->first].parameters["editable"]){
//            nodes_to_remove.push_back(it1->first);
//        }
//    }
//    for(int i=0; i<nodes_to_remove.size(); i++){
//        remove_node(nodes_to_remove[i]);
//    }
}

#endif