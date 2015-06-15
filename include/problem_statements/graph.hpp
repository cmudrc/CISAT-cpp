#ifndef PROBLEM_STATEMENTS__GRAPH_HPP
#define PROBLEM_STATEMENTS__GRAPH_HPP

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <cfloat>
#include <algorithm>
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
        Edge(void);
        int initial_node;
        int terminal_node;
        std::map<std::string, long double> parameters;
    };

    // Containers
    std::map<int, Node> nodes;
    std::map<int, Edge> edges;
    std::map<int, std::map<int, int> > connectivity_map;

    int node_id_counter;
    int edge_id_counter;

    // Functions for construction
    void add_edge(int n1, int n2);
    void add_node(void);

    // Functions for removal
    void remove_edge(int e);
    void remove_node(int n);

    // Navigating graph
    bool directed_edge_exists(int n1, int n2);
    bool undirected_edge_exists(int n1, int n2);
    bool is_connected(void);

    // Breadth-first search
    bool breadth_first_search(int n1, int n2);
    bool depth_first_search(int n1, int n2);

    // Sharing graph
    void print_undirected_connectivity_matrix(std::string label);
};

#endif