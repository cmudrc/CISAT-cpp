#include "../../include/problem_statements/graph.hpp"

Graph::Graph(void) {
    node_id_counter = -1;
    edge_id_counter = -1;
}


Graph::Node::Node(void) {};


void Graph::Node::remove_incoming_edge(int e) {
    for( std::vector<int>::iterator iter = incoming_edges.begin(); iter != incoming_edges.end(); ++iter ) {
        if( *iter == e ) {
            incoming_edges.erase( iter );
            break;
        }
    }
}


void Graph::Node::remove_outgoing_edge(int e) {
    for( std::vector<int>::iterator iter = outgoing_edges.begin(); iter != outgoing_edges.end(); ++iter ) {
        if( *iter == e ) {
            outgoing_edges.erase( iter );
            break;
        }
    }
}


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
    nodes[n1].outgoing_edges.push_back(edge_id_counter);
    nodes[n2].incoming_edges.push_back(edge_id_counter);

    // Add to the connectivity map
    connectivity_map[n1][n2] = edge_id_counter;
}


void Graph::add_node(void) {
    // Increment teh counter
    node_id_counter++;

    // Add the node
    nodes[node_id_counter] = Node();
}


void Graph::remove_edge(int e) {
    // Remove from connectivity map
    connectivity_map[edges[e].initial_node].erase(edges[e].initial_node);

    // Remove the reference from initial and terminal nodes
    nodes[edges[e].initial_node].remove_outgoing_edge(e);
    nodes[edges[e].terminal_node].remove_incoming_edge(e);

    // Remove the edge itself from edgelist
    edges.erase(e);
}


void Graph::remove_node(int n) {
    // Remove from connectivity map
    connectivity_map.erase(n);

    // Pull valid junction addition and edge deletion moves
    int k;
    for (std::map<int, Node>::iterator it1 =nodes.begin(); it1 !=nodes.end(); it1++) {
        k = (it1->first);
        connectivity_map[k].erase(n);
    }

    // Remove edges attached to the node
    for(int i=0; i<nodes[n].outgoing_edges.size(); i++) {
        edges.erase(nodes[n].outgoing_edges[i]);
    }
    for(int i=0; i<nodes[n].incoming_edges.size(); i++) {
        edges.erase(nodes[n].incoming_edges[i]);
    }

    // Remove the node itself
    nodes.erase(n);
}


// Indicates whether or not a directed edge exists between the two nodes
bool Graph::directed_edge_exists(int n1, int n2) {
    return (connectivity_map.count(n1) == 1 && connectivity_map[n1].count(n2) == 1);
}


// Indicates whether or not an edge exists between the two ndoes
bool Graph::undirected_edge_exists(int n1, int n2) {
    return (directed_edge_exists(n1, n2) || directed_edge_exists(n2, n1));
}


// Breadth first search for path between two nodes
bool Graph::breadth_first_search(int n1, int n2) {
    // TODO: Define BFS algorithm
    return true;
}


// Depth first search for path between two nodes
bool Graph::depth_first_search(int n1, int n2) {
    // TODO: Define DFS algorithm
    return true;
}