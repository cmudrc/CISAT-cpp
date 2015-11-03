//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─graph.cpp

#include "../../include/problem_statements/graph.hpp"

Graph::Graph(void) {
    node_id_counter = -1;
    edge_id_counter = -1;
    number_of_nodes = 0;
    number_of_edges = 0;
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

std::vector<int> Graph::get_neighbors(int n){
    std::vector<int> neighbors;
    int idx;
    for(int i=0; i<nodes[n].incoming_edges.size(); i++){
        idx = nodes[n].incoming_edges[i];
        neighbors.push_back(edges[idx].initial_node);
    }
    for(int i=0; i<nodes[n].outgoing_edges.size(); i++){
        idx = nodes[n].outgoing_edges[i];
        neighbors.push_back(edges[idx].terminal_node);
    }

    return neighbors;
}


// Find the edges that two
std::vector<int> Graph::find_common_neighbors(int n1, int n2){
    // Make vectors to store the two initial nodes
    std::vector<int> neighbors1 = get_neighbors(n1);
    std::vector<int> neighbors2 = get_neighbors(n2);;
    std::vector<int> matches;

    // Find the matches in the two lists
    for(int i=0; i<neighbors1.size(); i++){
        for(int j=0; j<neighbors2.size(); j++){
            if(neighbors1[i]==neighbors2[j]){
                matches.push_back(neighbors1[i]);
            }
        }
    }
    return matches;
}


Graph::Edge::Edge() {};
Graph::Edge::Edge(int n1, int n2) {
    initial_node = n1;
    terminal_node = n2;
};


void Graph::add_edge(int n1, int n2) {
    // Increment counter
    edge_id_counter++;
    number_of_edges++;

    // Make the edge
    edges[edge_id_counter] = Edge(n1, n2);

    // Tell the nodes they're attached
    nodes[n1].outgoing_edges.push_back(edge_id_counter);
    nodes[n2].incoming_edges.push_back(edge_id_counter);

    // Add to the connectivity map
    connectivity_map[n1][n2] = edge_id_counter;
}


void Graph::add_node(void) {
    // Increment teh counter
    node_id_counter++;
    number_of_nodes++;

    // Add the node
    nodes[node_id_counter] = Node();
}


void Graph::remove_edge(int e) {
    // Remove from connectivity map
    connectivity_map[edges[e].initial_node].erase(edges[e].terminal_node);

    // Remove the reference from initial and terminal nodes
    nodes.at(edges[e].initial_node).remove_outgoing_edge(e);
    nodes.at(edges[e].terminal_node).remove_incoming_edge(e);

    // Remove the edge itself from edgelist
    edges.erase(e);
    number_of_edges--;
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
    std::vector<int> temp_out = nodes[n].outgoing_edges;
    for(int i=0; i<temp_out.size(); i++) {
        remove_edge(temp_out[i]);
    }
    std::vector<int> temp_in = nodes[n].incoming_edges;
    for(int i=0; i<temp_in.size(); i++) {
        remove_edge(temp_in[i]);
    }

    // Remove the node itself
    nodes.erase(n);
    number_of_nodes--;
}


// Indicates whether or not a directed edge exists between the two nodes
bool Graph::directed_edge_exists(int n1, int n2) {
    return (connectivity_map.count(n1) == 1 && connectivity_map[n1].count(n2) == 1);
}


// Indicates whether or not an edge exists between the two ndoes
bool Graph::undirected_edge_exists(int n1, int n2) {
    return (directed_edge_exists(n1, n2) || directed_edge_exists(n2, n1));
}

int Graph::is_connected(void) {
    int penalty = 0;

    std::vector< std::vector<int> > full_con_mat(static_cast <unsigned long> (number_of_nodes),
                                                 std::vector<int> (static_cast<unsigned long> (number_of_nodes), 0));
    int i=0;
    int j=0;

    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        for (std::map<int, Node>::iterator it2 = nodes.begin(); it2 != nodes.end(); it2++) {
            if (undirected_edge_exists(it1->first, it2->first)) {
                full_con_mat[j][i] = 1;
            }
            i++;
        }
        i=0;
        j++;
    }
    full_con_mat = matrix_power(full_con_mat, number_of_nodes);

    for(i=0; i<number_of_nodes; i++) {
        for(j=0; j<number_of_nodes; j++) {
            if (full_con_mat[i][j] == 0) penalty ++;
        }
    }

    return penalty;
}


std::vector<int> Graph::get_node_ids(std::string param, long double value){
    std::vector<int> list;
    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        if (nodes[it1->first].parameters[param] == value) {
            list.push_back(it1->first);
        }
    }
    return list;
}


std::vector<int> Graph::get_edge_ids(std::string param, long double value){
    std::vector<int> list;
    for (std::map<int, Edge>::iterator it1 = edges.begin(); it1 != edges.end(); it1++) {
        if (edges[it1->first].parameters[param] == value) {
            list.push_back(it1->first);
        }
    }
    return list;
}


void Graph::print_undirected_connectivity_matrix(std::string label) {
    std::cout << std::endl << "    ";
    for (std::map<int, Node>::iterator it2 = nodes.begin(); it2 != nodes.end(); it2++) {
        std::cout << nodes[it2->first].parameters[label] << " ";
    }
    std::cout << std::endl << "    ";
    for (std::map<int, Node>::iterator it2 = nodes.begin(); it2 != nodes.end(); it2++) {
        std::cout << "| ";
    }
    std::cout << std::endl;

    for (std::map<int, Node>::iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        std::cout << nodes[it1->first].parameters[label] << " — ";
        for (std::map<int, Node>::iterator it2 = nodes.begin(); it2 != nodes.end(); it2++) {
            if((it1->first) == (it2->first)) {
                std::cout << "\\ ";
            }
            else if(undirected_edge_exists(it1->first, it2->first)) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Graph::print_directed_edge_list(void) {
    for(std::map<int, Edge>::iterator iter= edges.begin(); iter != edges.end(); ++iter) {
        std::cout << iter->first << "\t" << edges[iter->first].initial_node << "\t" << edges[iter->first].terminal_node << std::endl;
    }
}

long double Graph::euclidean_distance(int n1, int n2) {
    return std::sqrt(
            std::pow(nodes[n1].parameters["x"] - nodes[n2].parameters["x"], 2)
            + std::pow(nodes[n1].parameters["y"] - nodes[n2].parameters["y"], 2)
            + std::pow(nodes[n1].parameters["z"] - nodes[n2].parameters["z"], 2)
    );
}
