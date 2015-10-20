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
const  long double    Solution::Fy              = 344*std::pow(10,6); // Pa
const  long double    Solution::rho             = 7870; // kg/m3

// TODO: Add calculation of area and moment of inertia
const std::vector< long double > Solution::member_radius  = {0.005, 0.010, 0.015, 0.020, 0.025,
                                                             0.030, 0.035, 0.040, 0.045, 0.050};
const std::vector< long double > Solution::wall_thickness = {0.005/15, 0.010/15, 0.015/15, 0.020/15, 0.025/15,
                                                             0.030/15, 0.035/15, 0.040/15, 0.045/15, 0.050/15};

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
        {"Fy", -200000.00}, // [N]
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
        {"Fy", -200000.00}, // [N]
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
        {"Fy", 0.00}, // [N]
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
        {"Fy", 0.00}, // [N]
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
        {"radius", 4}
    }, {
        {"initial",  1},
        {"terminal", 2},
        {"radius", 4}
    }, {
        {"initial",  2},
        {"terminal", 3},
        {"radius", 4}
    }, {
        {"initial",  3},
        {"terminal", 4},
        {"radius", 4}
    }, {
        {"initial",  5},
        {"terminal", 6},
        {"radius", 4}
    }, {
        {"initial",  6},
        {"terminal", 7},
        {"radius", 4}
    }, {
        {"initial",  0},
        {"terminal", 5},
        {"radius", 4}
    }, {
        {"initial",  1},
        {"terminal", 5},
        {"radius", 4}
    }, {
        {"initial",  5},
        {"terminal", 2},
        {"radius", 4}
    }, {
        {"initial",  6},
        {"terminal", 2},
        {"radius", 4}
    }, {
        {"initial",  7},
        {"terminal", 2},
        {"radius", 4}
    }, {
        {"initial",  3},
        {"terminal", 7},
        {"radius", 4}
    }, {
        {"initial",  4},
        {"terminal", 7},
        {"radius", 4}
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
        add_member(seed_edge_parameters[i]["initial"], seed_edge_parameters[i]["terminal"], seed_edge_parameters[i]["radius"], true);
    }
}

void Solution::compute_quality(void) {
    // Define some things
    long double mass = 0;
    long double FOS = LDBL_MAX;
    long double FOS_penalty;

    if (is_valid()) {
        // Compute the force-based solution for the truss
        compute_truss_forces();

        // Compute the mass
        for (std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); ++it1) {
            mass += edges[it1->first].parameters["m"];
            if (edges[it1->first].parameters["FOS_y"] < FOS) {
                FOS = edges[it1->first].parameters["FOS_y"];
            }
            if (edges[it1->first].parameters["FOS_b"] < FOS) {
                FOS = edges[it1->first].parameters["FOS_b"];
            }
        }

        print(FOS);

        // Compute FOS penalty
        if(FOS < LDBL_MAX) {
            if (FOS > 1.25) {
                FOS_penalty = 0;
            }
            else {
                FOS_penalty = std::pow(10, 4) * std::pow(1.25 - FOS, 2);
            }
        } else {
            mass = std::pow(10, 10);
            FOS_penalty = std::pow(10, 10);
        }
    } else {
        mass = std::pow(10, 10);
        FOS_penalty = std::pow(10, 10);
    }

    quality[0] = mass + FOS_penalty;
    std::cout << quality[0] << " " << mass << " "  << FOS << std::endl;

}

void Solution::compute_truss_forces(void) {
    // Initialize things
    std::vector<std::vector<long double> > K(static_cast<unsigned long>(3 * number_of_nodes),
                                             std::vector<long double>(static_cast<unsigned long>(3 * number_of_nodes),
                                                                      0.0));

    // Get the vector that will relate entries in the node map to entries in the global stiffness matrix
    std::map<int, int> node_id_map;
    int counter = 0;
    for (std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        node_id_map[it->first] = counter;
        counter++;
    }

    // Define a matrix that will later to be used to hold deflections and other things
    std::vector<std::vector<long double> > deflections(3, std::vector<long double>(static_cast<unsigned long>(number_of_nodes), 0));
    std::vector<std::vector<long double> > loads(3, std::vector<long double>(static_cast<unsigned long>(number_of_nodes), 0));

    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
        int idx = node_id_map[it1->first];
        deflections[0][idx] = 1 - nodes[it1->first].parameters["rx"];
        deflections[1][idx] = 1 - nodes[it1->first].parameters["ry"];
        deflections[2][idx] = 1 - nodes[it1->first].parameters["rz"];
        loads[0][idx] = nodes[it1->first].parameters["Fx"];
        loads[1][idx] = nodes[it1->first].parameters["Fy"];
        loads[2][idx] = nodes[it1->first].parameters["Fz"];
    }

    // Find out which joints can deflect
    std::vector<long double> ff;
    std::vector<long double> loads_ff;
    counter = 0;
    for (int i = 0; i < number_of_nodes; i++) {
        for (int j = 0; j < 3; j++) {
            if (deflections[j][i] == 1) {
                ff.push_back(counter);
                loads_ff.push_back(loads[j][i]);
            }
            counter++;
        }
    }

    // Build the global stiffess matrix
    int idx1, idx2, key1, key2;
    long double ux, uy, uz;
    std::vector<int> ee(6, 0);
    std::vector<long double> uu(6, 0.0);
    std::vector<std::vector<long double>> element_stiffness(number_of_edges, std::vector<long double>(3, 0.0));
    for (std::map<int, Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
        int k = (it->first);
        key1 = edges[k].initial_node;
        key2 = edges[k].terminal_node;
        idx1 = node_id_map[key1];
        idx2 = node_id_map[key2];
        ux = (nodes[key1].parameters["x"] - nodes[key2].parameters["x"]) / edges[k].parameters["L"];
        uy = (nodes[key1].parameters["y"] - nodes[key2].parameters["y"]) / edges[k].parameters["L"];
        uz = (nodes[key1].parameters["z"] - nodes[key2].parameters["z"]) / edges[k].parameters["L"];
        long double EAL = E * edges[k].parameters["A"] / edges[k].parameters["L"];
        edges[k].parameters["kx"] = EAL*ux;
        edges[k].parameters["ky"] = EAL*uy;
        edges[k].parameters["kz"] = EAL*uz;
        uu = {ux, uy, uz, -ux, -uy, -uz};
        ee = {3 * idx1, 3 * idx1 + 1, 3 * idx1 + 2, 3 * idx2, 3 * idx2 + 1, 3 * idx2 + 2};
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                K[ee[i]][ee[j]] += EAL * uu[i] * uu[j];
            }
        }
    }

    // Solve for displacements
    std::vector<std::vector<long double> > Kff(ff.size(), std::vector<long double>(ff.size() + 1, 0.0));
    for (int i = 0; i < ff.size(); i++) {
        for (int j = 0; j < ff.size(); j++) {
            Kff[i][j] = K[ff[i]][ff[j]];
        }
        Kff[i][ff.size()] = loads_ff[i];
    }
    std::vector<long double> deflections_compact = gauss(Kff);

    // Fit the compacted deflection matrix back into the original
    counter = 0;
    for (int i = 0; i < number_of_nodes; i++) {
        for (int j = 0; j < 3; j++) {
            if (deflections[j][i] == 1) {
                deflections[j][i] = deflections_compact[counter];
                counter++;
            }
        }
    }

    // From displacements, solve for forces
    for (std::map<int, Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
        // Define a few things
        int k = (it->first);
        idx1 = node_id_map[edges[k].initial_node];
        idx2 = node_id_map[edges[k].terminal_node];

        // Define the force
        edges[k].parameters["F"] =   edges[k].parameters["kx"] * (deflections[0][idx1] - deflections[0][idx2])
                                   + edges[k].parameters["ky"] * (deflections[1][idx1] - deflections[1][idx2])
                                   + edges[k].parameters["kz"] * (deflections[2][idx1] - deflections[2][idx2]);

        // Calculate factor of safety against yielding
        edges[k].parameters["FOS_y"] = std::abs((Fy*edges[k].parameters["A"])/edges[k].parameters["F"]);

        // Calculate force of safety
        if (edges[k].parameters["F"] < 0) {
            edges[k].parameters["FOS_b"] = -(std::pow(M_PI, 2) * E * edges[k].parameters["I"]/std::pow(edges[k].parameters["L"], 2))/edges[k].parameters["F"];
        } else {
            edges[k].parameters["FOS_b"] = LDBL_MAX;
        }
    }
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
void Solution::add_member(int n1, int n2, int r, bool editable){
    // Add the edge to the graph
    add_edge(n1, n2);

    // Add parameters to the edges
    edges[edge_id_counter].parameters["editable"] = editable;
    edges[edge_id_counter].parameters["r"] = r;
    edges[edge_id_counter].parameters["t"] = r;
    update_length(edge_id_counter);
    update_sectional_properties(edge_id_counter);
}


void Solution::add_member(void){
    // Define some things
    std::vector<int> editable = get_node_ids("z", 0.00);
    std::vector<long double> weights(editable.size(), 1.0);

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
        std::vector<long double> weights(editable.size(), 1.0);
        remove_edge(editable[weighted_choice(weights)]);
    }
}


void Solution::remove_joint(void) {
    // Define some things
    std::vector<int> editable = get_node_ids("editable", true);

    // Make a selection
    int idx;
    if(editable.size() > 0){
        std::vector<long double> weights(editable.size(), 1.0);
        idx = weighted_choice(weights);
        remove_node(editable[idx]);
    }
}


void Solution::change_size_single(void){
    // Define some things
    std::vector<int> editable = get_edge_ids("editable", true);
    std::vector<long double> weights(editable.size(), 1.0);

    // Make a selection
    int idx = weighted_choice(weights);

    // Increase the size of the selected edge
    int inc_dec = uniform_int(1, 0)*2 - 1;

    if ((edges[editable[idx]].parameters["r"] + inc_dec) < member_radius.size()
        && (edges[editable[idx]].parameters["r"] + inc_dec) >= 0){
        edges[editable[idx]].parameters["r"] += inc_dec;
        edges[editable[idx]].parameters["t"] += inc_dec;
        update_sectional_properties(editable[idx]);
    }
}

void Solution::change_size_all(void){
    // Define some things
    std::vector<int> editable = get_edge_ids("editable", true);

    // Decide whether ot increase or decrease
    int inc_dec = uniform_int(1, 0)*2 - 1;

    for(int i=0; i<editable.size(); i++){
        if ((edges[editable[i]].parameters["r"] + inc_dec) < member_radius.size()
            && (edges[editable[i]].parameters["r"] + inc_dec) >= 0){
            edges[editable[i]].parameters["r"] += inc_dec;
            edges[editable[i]].parameters["t"] += inc_dec;
            update_sectional_properties(editable[i]);
        }
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
            update_length(it1->first);
        }
    }
}

void Solution::add_joint_and_attach(void){
    // Add the new joint
    add_joint(uniform(-5, 5), uniform(-3, 3), 0.0, true);

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
        add_member(node_id_counter, reverse_map[idx], 4, true);
    }
}


void Solution::update_length(int e){
    // Update the length
    edges[e].parameters["L"] = euclidean_distance(edges[e].initial_node, edges[e].terminal_node);
}


void Solution::update_sectional_properties(int e){
    // Update the area
    long double outer = member_radius[edges[e].parameters["r"]];
    long double inner = outer - wall_thickness[edges[e].parameters["t"]];
    edges[e].parameters["A"] = M_PI*(std::pow(outer, 2) - std::pow(inner, 2));

    // Update the area moment of inertia
    edges[e].parameters["I"] = M_PI*(std::pow(2*outer, 4) - std::pow(2*inner, 4))/64;

    // Compute the mass of the member
    edges[e].parameters["m"] = edges[e].parameters["L"]*edges[e].parameters["A"]*rho;
}


// Function to ensure that the solution is valid
int Solution::is_valid(void) {
    // Make sure forces nodes are connected by 2
    bool LOADS = true;

    // Make sure supports are connected
    bool SUPPORTS = true;

    // Make sure at least statically determinant
    bool STAT_DET = false;
    if (number_of_edges + 5 >= 2*number_of_nodes) {
        STAT_DET = true;
    }

    return LOADS && SUPPORTS && STAT_DET;
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
                       edges[it1->first].parameters["r"]);
    }


    x3d.close_file();
}
