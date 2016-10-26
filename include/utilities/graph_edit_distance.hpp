#ifndef UTILITIES__GRAPH_EDIT_DISTANCE_HPP
#define UTILITIES__GRAPH_EDIT_DISTANCE_HPP

#include <vector>
#include <cmath>

int minimum_graph_edit_distance(std::vector< std::vector<int> > A, std::vector< std::vector<int> > B, int nodes_to_hold);

int compute_difference(std::vector< std::vector<int> > A, std::vector< std::vector<int> > B, int nA, int nB);

#endif
