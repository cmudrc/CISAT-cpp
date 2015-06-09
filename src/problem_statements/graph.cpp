#include "../../include/problem_statements/graph.hpp"

Graph::Node::Node(void) {};

Graph::Edge::Edge(void) {};

void Graph::add_edge(int n1, int n2) {
    // Increment counter
    edge_id_counter++;

    // Make the edge
    edges[edge_id_counter] = Edge();

    // Attach it to nodes
    edges[edge_id_counter].initial_node = n1;
    edges[edge_id_counter].terminal_node = n2;

    // Tell the nodes they're attached
    nodes[n1].attached_edges.push_back(edge_id_counter);
    nodes[n2].attached_edges.push_back(edge_id_counter);
}

void Graph::add_node(void) {
    // Increment teh counter
    node_id_counter++;

    // Add the node
    nodes[node_id_counter] = Node();
}

void Graph::remove_edge(int e) {
    // Remove the reference from initial node via erase/remove idiom
    int n = edges[e].initial_node;
    nodes[n].attached_edges.erase(
            std::remove( nodes[n].attached_edges.begin(), nodes[n].attached_edges.end(), e),
            nodes[n].attached_edges.end()
    );

    // Remove the reference from terminal node via erase/remove idiom
    n = edges[e].terminal_node;
    nodes[n].attached_edges.erase(
            std::remove( nodes[n].attached_edges.begin(), nodes[n].attached_edges.end(), e),
            nodes[n].attached_edges.end()
    );

    // Remove the edge itself from edgelist
    edges.erase(e);
}

void Graph::remove_node(int n) {
    // Remove edges attached to the node
    for(int i=0; i<nodes[n].attached_edges.size(); i++) {
        edges.erase(nodes[n].attached_edges[i]);
    }

    // Remove the node itself
    nodes.erase(n);
}

void update_connectivity_matrix(void) {
    // Make a list of nodes
}