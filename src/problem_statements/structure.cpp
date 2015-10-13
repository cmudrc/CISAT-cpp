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

// Problem definition
std::vector< std::map<std::string, long double> > Solution::seed_graph_parameters = {
    {
        {"x", 0.00}, // [m]
        {"y", 10.00}, // [m]
        {"z", 0.00}, // [m]
        {"F", 35000.00}, // [N]
        {"rx", 0}, // [bool]
        {"ry", 0}, // [bool]
        {"rz", 1} // [bool]
    }, {
        {"x", 1.00}, // [m]
        {"y", 10.00}, // [m]
        {"z", 0.00}, // [m]
        {"F", 0.00}, // [N]
        {"rx", 1}, // [bool]
        {"ry", 1}, // [bool]
        {"rz", 1} // [bool]
    }, {
        {"x", -1.00}, // [m]
        {"y", 0.00}, // [m]
        {"z", 0.00}, // [m]
        {"F", 0.00}, // [N]
        {"rx", 1}, // [bool]
        {"ry", 1}, // [bool]
        {"rz", 1} // [bool]
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


void get_valid_moves(void){

}


void apply_move_operator(int move_type, int move_number){

}


void save_as_x3d(std::string save_to_file) {
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


void compute_quality(void) {}

void comput_truss_forces(void) {}
    // Initialize things
    std::vector< std::vector <long double> >  tj(3, std::vector<long double>(static_cast<unsigned long>(number_of_edges), 0));
    std::vector< std::vector <long double> > dof(static_cast<unsigned long>(3*number_of_nodes),
                                                 std::vector<long double>(static_cast<unsigned long>(number_of_nodes), 0.0));

    // Get the vector that will relate entries in the node map to entries in the global stiffness matrix
    std::map<int, int> node_id_map;
    int counter = 0;
    for(std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        node_id_map[(it->first)] = counter;
        counter++;
    }

    // Define a matrix that will later to be used to hold deflections and other things
    std::vector< std::vector <long double> >  deflections(3, std::vector<long double>(static_cast<unsigned long>(number_of_nodes), 0));
    for(std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
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
    int idx1 = 0;
    int idx2 = 0;
    for (std::map<int, Edge>::iterator it=edges.begin(); it!=edges.end(); it++) {
        k = (it->first);
        idx1 = node_id_map[edges[k].initial_node];
        idx2 = node_id_map[edges[k].terminal_node];
    }


}



void create_seed_graph(void);

// Move operators
void add_member(int n1, int n2, int d, bool editable);
void add_joint(long double x, long double y, long double z, bool editable);


void remove_member(int e) {
    remove_edge(e);
}


void remove_joint(int n) {
    remove_node(n);
}


void increase_member_size(int e) {
    edges[e].parameters["d"]++;
}


void decrease_member_size(int e);
void move_joint(int n, long double dx, long double dy, long double dz);
void brace_member(int e);
void add_joint_and_attach(long double x, long double y, long double z);


// Function to ensure that the solution is valid
int is_valid(void) {
    return is_connected();
}