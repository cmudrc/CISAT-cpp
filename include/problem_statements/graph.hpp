//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  include
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─graph.hpp

#ifndef PROBLEM_STATEMENTS__GRAPH_HPP
#define PROBLEM_STATEMENTS__GRAPH_HPP

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <cfloat>
#include <algorithm>
#include <cstdlib>
#include "../utilities/custom_print.hpp"
#include "../utilities/matrix_operations.hpp"

class Graph {
public:
    Graph(void);

    // Structures
    struct Node {
        Node(void);
        void remove_incoming_edge(int e);
        void remove_outgoing_edge(int e);
        std::vector<int> incoming_edges;
        std::vector<int> outgoing_edges;
        std::map<std::string, long double> parameters;
    };

    struct Edge {
        Edge();
        Edge(int n1, int n2);
        int initial_node;
        int terminal_node;
        std::map<std::string, long double> parameters;
    };

    // Containers
    std::map<int, Node> nodes;
    std::map<int, Edge> edges;
    std::map<int, std::map<int, int> > connectivity_map;

    // Counters
    int number_of_nodes;
    int number_of_edges;
    int node_id_counter;
    int edge_id_counter;

    // Functions for construction
    void add_edge(int n1, int n2);
    void add_node(void);

    // Functions for removal
    void remove_edge(int e);
    void remove_node(int n);

    // Not valid without specific things
    long double euclidean_distance(int n1, int n2);

    // Navigating graph
    bool directed_edge_exists(int n1, int n2);
    bool undirected_edge_exists(int n1, int n2);
    int is_connected(void);

    // Breadth-first search
    bool breadth_first_search(int n1, int n2);
    bool depth_first_search(int n1, int n2);

    // Displaying graph
    void print_undirected_connectivity_matrix(std::string label);
    void print_directed_edge_list(void);
};

#endif