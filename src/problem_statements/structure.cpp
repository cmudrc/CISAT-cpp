//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─structure.cpp

#include "../../include/problem_statements/structure.hpp"

// Graph grammar characteristics
const  unsigned long  Solution::number_of_move_ops   = 7;
const  unsigned long  Solution::number_of_objectives = 1;
const  std::string    Solution::name                 = "Gravity Fed Fluid Network";
const  long double    Solution::goal                 = 0.0;

// Material constants
const  long double    Solution::E               = 209*std::pow(10,9); // Pa
const  long double    Solution::Fy              = 250*std::pow(10,6); // Pa

//
const std::vector< long double > pipe_diam = {0.02, 0.04, 0.06, 0.08, 0.10};

// Problem definition
std::vector< std::map<std::string, long double> > Solution::seed_node_parameters = {
    {
        {"x", -5.00}, // [m]
        {"y",  0.00}, // [m]
        {"z",  0.00}, // [m]
        {"Fx", 0.00}, // [N]
        {"Fy", 0.00}, // [N]
        {"Fz", 0.00}, // [N]
        {"rx", 1}, // [bool]
        {"ry", 1}, // [bool]
        {"rz", 1}, // [bool]
        {"editable", false}
    }, {
        {"x", -2.00}, // [m]
        {"y",  0.00}, // [m]
        {"z",  0.00}, // [m]
        {"Fx", 0.00}, // [N]
        {"Fy", -3500.00}, // [N]
        {"Fz", 0.00}, // [N]
        {"rx", 0}, // [bool]
        {"ry", 0}, // [bool]
        {"rz", 1}, // [bool]
        {"editable", false}
    }, {
        {"x",  1.00}, // [m]
        {"y",  0.00}, // [m]
        {"z",  0.00}, // [m]
        {"Fx", 0.00}, // [N]
        {"Fy", 0.00}, // [N]
        {"Fz", 0.00}, // [N]
        {"rx", 0}, // [bool]
        {"ry", 1}, // [bool]
        {"rz", 1}, // [bool]
        {"editable", false}
    }, {
        {"x",  3.00}, // [m]
        {"y",  0.00}, // [m]
        {"z",  0.00}, // [m]
        {"Fx", 0.00}, // [N]
        {"Fy", -3500.00}, // [N]
        {"Fz", 0.00}, // [N]
        {"rx", 0}, // [bool]
        {"ry", 0}, // [bool]
        {"rz", 1}, // [bool]
        {"editable", false}
    }, {
        {"x",  5.00}, // [m]
        {"y",  0.00}, // [m]
        {"z",  0.00}, // [m]
        {"Fx", 0.00}, // [N]
        {"Fy", 0.00}, // [N]
        {"Fz", 0.00}, // [N]
        {"rx", 1}, // [bool]
        {"ry", 1}, // [bool]
        {"rz", 1}, // [bool]
        {"editable", false}
    }, {
        {"x", -2.00}, // [m]
        {"y",  2.00}, // [m]
        {"z",  0.00}, // [m]
        {"Fx", 0.00}, // [N]
        {"Fy", -3500.00}, // [N]
        {"Fz", 0.00}, // [N]
        {"rx", 0}, // [bool]
        {"ry", 0}, // [bool]
        {"rz", 1}, // [bool]
        {"editable", true}
    }, {
        {"x",  1.00}, // [m]
        {"y",  2.00}, // [m]
        {"z",  0.00}, // [m]
        {"Fx", 0.00}, // [N]
        {"Fy", 0.00}, // [N]
        {"Fz", 0.00}, // [N]
        {"rx", 0}, // [bool]
        {"ry", 0}, // [bool]
        {"rz", 1}, // [bool]
        {"editable", true}
    }, {
        {"x",  3.00}, // [m]
        {"y",  2.00}, // [m]
        {"z",  0.00}, // [m]
        {"Fx", 0.00}, // [N]
        {"Fy", -3500.00}, // [N]
        {"Fz", 0.00}, // [N]
        {"rx", 0}, // [bool]
        {"ry", 0}, // [bool]
        {"rz", 1}, // [bool]
        {"editable", true}
    }
};

// Problem definition
std::vector< std::map<std::string, long double> > Solution::seed_edge_parameters = {
    {
        {"initial",  0},
        {"terminal", 1},
        {"diameter", 4}
    }, {
        {"initial",  1},
        {"terminal", 2},
        {"diameter", 4}
    }, {
        {"initial",  2},
        {"terminal", 3},
        {"diameter", 4}
    }, {
        {"initial",  3},
        {"terminal", 4},
        {"diameter", 4}
    }, {
        {"initial",  5},
        {"terminal", 6},
        {"diameter", 4}
    }, {
        {"initial",  6},
        {"terminal", 7},
        {"diameter", 4}
    }, {
        {"initial",  0},
        {"terminal", 5},
        {"diameter", 4}
    }, {
        {"initial",  1},
        {"terminal", 5},
        {"diameter", 4}
    }, {
        {"initial",  5},
        {"terminal", 2},
        {"diameter", 4}
    }, {
        {"initial",  6},
        {"terminal", 2},
        {"diameter", 4}
    }, {
        {"initial",  7},
        {"terminal", 2},
        {"diameter", 4}
    }, {
        {"initial",  3},
        {"terminal", 7},
        {"diameter", 4}
    }, {
        {"initial",  4},
        {"terminal", 7},
        {"diameter", 4}
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

void Solution::create_seed_graph(void){
    // Add all joints
    for(int i=0; i < seed_node_parameters.size(); i++) {
        // Add the node
        add_node();

        // Add the values
        nodes[node_id_counter].parameters["x"] = seed_node_parameters[i]["x"];
        nodes[node_id_counter].parameters["y"] = seed_node_parameters[i]["y"];
        nodes[node_id_counter].parameters["z"] = seed_node_parameters[i]["z"];
        nodes[node_id_counter].parameters["rx"] = seed_node_parameters[i]["rx"];
        nodes[node_id_counter].parameters["ry"] = seed_node_parameters[i]["ry"];
        nodes[node_id_counter].parameters["rz"] = seed_node_parameters[i]["rz"];
        nodes[node_id_counter].parameters["Fx"] = seed_node_parameters[i]["Fx"];
        nodes[node_id_counter].parameters["Fy"] = seed_node_parameters[i]["Fy"];
        nodes[node_id_counter].parameters["Fz"] = seed_node_parameters[i]["Fz"];
        nodes[node_id_counter].parameters["editable"] = seed_node_parameters[i]["editable"];
    }

    // Connect these joints
    for(int i=0; i < seed_edge_parameters.size(); i++) {
        add_member(seed_edge_parameters[i]["initial"], seed_edge_parameters[i]["terminal"], seed_edge_parameters[i]["diameter"], true);
    }
}

void Solution::compute_quality(void) {
    quality[0] = -(number_of_edges + number_of_nodes);
}

void Solution::compute_truss_forces(void) {
    // Initialize things
    std::vector< std::vector <long double> >  tj(3, std::vector<long double>(static_cast<unsigned long>(number_of_edges), 0));
    std::vector< std::vector <long double> > K(static_cast<unsigned long>(3*number_of_nodes),
                                                 std::vector<long double>(static_cast<unsigned long>(number_of_nodes), 0.0));

    // Get the vector that will relate entries in the node map to entries in the global stiffness matrix
    std::map<int, int> node_id_map;
    int counter = 0;
    for(std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        node_id_map[(it->first)] = counter;
        counter++;
    }

    // Define a matrix that will later to be used to hold deflections and other things
    int idx;
    std::vector< std::vector <long double> >  deflections(3, std::vector<long double>(static_cast<unsigned long>(number_of_nodes), 0));
    for(std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
        idx = node_id_map[it1->first];
        deflections[0][idx] = 1 - nodes[it1->first].parameters["rx"];
        deflections[1][idx] = 1 - nodes[it1->first].parameters["ry"];
        deflections[2][idx] = 1 - nodes[it1->first].parameters["rz"];
    }

    // Find out which joints can deflect
    std::vector<long double> ff;
    counter = 0;
    for(int i=0; i<number_of_nodes; i++) {
        for(int j=0; j<3; j++){
            if(deflections[j][i] == 1){
                ff.push_back(counter);
            }
            counter++;
        }
    }

    // Build the global stiffess matrix
    int k;
    int idx1;
    int idx2;
    long double ux;
    long double uy;
    long double uz;
    std::vector<int> ee(6, 0);
    std::vector<long double> uu(6, 0.0);
    for (std::map<int, Edge>::iterator it=edges.begin(); it!=edges.end(); it++) {
        k = (it->first);
        idx1 = node_id_map[edges[k].initial_node];
        idx2 = node_id_map[edges[k].terminal_node];
        ux = (nodes[idx1].parameters["x"] - nodes[idx2].parameters["x"])/edges[k].parameters["L"];
        uy = (nodes[idx1].parameters["y"] - nodes[idx2].parameters["y"])/edges[k].parameters["L"];
        uz = (nodes[idx1].parameters["z"] - nodes[idx2].parameters["z"])/edges[k].parameters["L"];
        uu = {ux, uy, uz, -ux, -uy, -uz};
        ee = {3*idx1 - 3, 3*idx1-2, 3*idx1-1, 3*idx2 - 3, 3*idx2-2, 3*idx2-1};
        for(int i=0; i<6; i++) {
            for(int j=0; j<6; j++) {
                K[ee[i]][ee[j]] += E*edges[k].parameters["A"]/edges[k].parameters["L"]*uu[i]*uu[j];
            }
        }
    }

    print(K);
}


void Solution::apply_move_operator(int move_type){
    switch(move_type) {
        case 0:
            add_member();
            break;
        case 1:
            remove_member();
            break;
        case 2:
            remove_joint();
            break;
        case 3:
            change_size_single();
            break;
        case 4:
            change_size_all();
            break;
        case 5:
            move_joint();
            break;
        case 6:
            add_joint_and_attach();
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

// Move operators
void Solution::add_member(int n1, int n2, int d, bool editable){
    // Add the edge to the graph
    add_edge(n1, n2);

    // Add parameters to the edges
    edges[edge_id_counter].parameters["editable"] = editable;
    edges[edge_id_counter].parameters["d"] = d;

    // Compute the length
    edges[edge_id_counter].parameters["L"] = euclidean_distance(n1, n2);
}


void Solution::add_member(void){
    // Define some things
    std::vector<int> editable = get_node_ids("z", 0.00);
    std::vector<long double> weights(editable.size(), 0.0);

    // Pick nodes to attach between
    int idx = weighted_choice(weights);
    weights[idx] = 0.0;
    int n1 = editable[idx];
    int n2 = editable[weighted_choice(weights)];

    // TODO Make sure the member doesn't already exist

    // Add the member
    add_member(n1, n2, 4, true);
}

void Solution::add_joint(long double x, long double y, long double z, bool editable){
    // Add the node
    add_node();

    // Add the coordinates
    nodes[node_id_counter].parameters["x"] = x;
    nodes[node_id_counter].parameters["y"] = y;
    nodes[node_id_counter].parameters["z"] = z;

    // Add other miscellaneous parameters, assuming joint is free
    nodes[node_id_counter].parameters["Fx"] = 0;
    nodes[node_id_counter].parameters["Fy"] = 0;
    nodes[node_id_counter].parameters["Fz"] = 0;
    nodes[node_id_counter].parameters["rx"] = 0;
    nodes[node_id_counter].parameters["ry"] = 0;
    nodes[node_id_counter].parameters["rz"] = 1;

    // Moveable or not
    nodes[node_id_counter].parameters["editable"] = editable;
}


void Solution::remove_member(void) {
    // Define some things
    std::vector<int> editable = get_edge_ids("editable", true);

    // Make a selection
    if(editable.size() > 0){
        std::vector<long double> weights(editable.size(), 0.0);
        remove_edge(editable[weighted_choice(weights)]);
    }
}


void Solution::remove_joint(void) {
    // Define some things
    std::vector<int> editable = get_node_ids("editable", true);

    // Make a selection
    if(editable.size() > 0){
        std::vector<long double> weights(editable.size(), 0.0);
        remove_node(editable[weighted_choice(weights)]);
    }
}


void Solution::change_size_single(void){
    // Define some things
    std::vector<int> editable = get_edge_ids("editable", true);
    std::vector<long double> weights(editable.size(), 0.0);

    // Make a selection
    int idx = weighted_choice(weights);

    // Increase the size of the selected edge
    int inc_dec = uniform_int(1, 0)*2 - 1;
    print(inc_dec);

    edges[editable[idx]].parameters["d"] += inc_dec;
}

void Solution::change_size_all(void){
    // Define some things
    std::vector<int> editable = get_edge_ids("editable", true);

    // Decide whether ot increase or decrease
    int inc_dec = uniform_int(1, 0)*2 - 1;
    print(inc_dec);

    for(int i=0; i<editable.size(); i++){
        edges[editable[i]].parameters["d"] += inc_dec;
    }
}


void Solution::move_joint(void){
    // Define a couple of things
    std::vector<int> editable = get_node_ids("editable", true);
    if(editable.size() > 0){
        std::vector<long double> weights(editable.size(), 1.0);

        // Select one to move at random
        int idx = weighted_choice(weights);

        // Move it somehow TODO: Make this more intelligent
        nodes[editable[idx]].parameters["x"] += uniform(-1.0, 1.0);
        nodes[editable[idx]].parameters["y"] += uniform(-1.0, 1.0);

        // Brute force length update TODO Avoid brute-forcedness
        for (std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); it1++) {
            edges[it1->first].parameters["L"] = euclidean_distance(edges[it1->first].initial_node, edges[it1->first].terminal_node);
        }
    }
}

void Solution::add_joint_and_attach(){
    // Find x y and z for new joint
    long double x = uniform(-2, 2);
    long double y = uniform(0, 15);
    long double z = 0;

    // Add the new joint
    add_joint(x, y, z, true);

    // Find distance between current joint and other joints
    std::vector<long double> distances;
    std::vector<int> reverse_map;
    for(std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++){
        distances.push_back(euclidean_distance(node_id_counter, it1->first));
        reverse_map.push_back(it1->first);
    }

    // Connect the newest joint to the three nearest existing joints
    long idx;
    for(int i=0; i<3; i++){
        idx = vector_argmin(distances);
        distances[idx] = LDBL_MAX;
        add_edge(node_id_counter, reverse_map[idx]);
    }
}


// Function to ensure that the solution is valid
int Solution::is_valid(void) {
    return is_connected();
}


void Solution::save_as_x3d(std::string save_to_file) {
    WriteX3D x3d;
    int n1, n2;

    x3d.open_file(save_to_file, -1, 1, 10);
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        x3d.write_sphere(nodes[it1->first].parameters["x"], nodes[it1->first].parameters["y"], nodes[it1->first].parameters["z"], 0.25);
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
