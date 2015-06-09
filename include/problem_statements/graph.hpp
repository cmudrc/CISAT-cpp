#ifndef PROBLEM_STATEMENTS__GRAPH_HPP
#define PROBLEM_STATEMENTS__GRAPH_HPP

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "../utilities/custom_print.hpp"

class Graph {
public:
    Graph(void);

    // Structures
    struct Node {
        Node(void);
        std::vector<int> attached_edges;
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

    int node_id_counter;
    int edge_id_counter;

    // Functions for construction
    void add_edge(int n1, int n2);
    void add_node(void);

    // Functions for removal
    void remove_edge(int e);
    void remove_node(int n);
};

#endif