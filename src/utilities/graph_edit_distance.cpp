#include "../../include/utilities/graph_edit_distance.hpp"

int graph_edit_distance(std::vector< std::vector<int> > A, std::vector< std::vector<int> > B, int nodes_to_hold) {
    int distance = 0;

    // Initialize sizes
    int nA = A.size();
    int nB = B.size();
    int n = 0;

    // Resize and swap as appropriate
    if(nA > nB) {
        // Store the size
        n = nA;

        // Resize B
        B.resize(n);
        for(int i=0; i<n; i++) {
            B[i].resize(n);
        }
    } else if (nB > nA) {
        // Store the size
        n = nB;

        // Resize A
        A.resize(n);
        for(int i=0; i<n; i++) {
            A[i].resize(n);
        }

    } else {
        n = nA;
    }

    // Compute the initial difference
    distance = compute_difference(A, B, nA, nB);



    return distance;
}


int compute_difference(std::vector< std::vector<int> > A, std::vector< std::vector<int> > B, int nA, int nB) {
    d = 0;
    n = A.size();

    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(A[i][j] != B[i][j]){
                d++;
            }
        }
    }

    return d + std::abs(nA - nB);
}