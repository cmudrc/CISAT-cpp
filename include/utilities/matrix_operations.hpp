#ifndef UTILITIES__MATRIX_OPERATIONS_HPP
#define UTILITIES__MATRIX_OPERATIONS_HPP

#include <vector>
#include <cmath>

std::vector<long double> gauss(std::vector< std::vector<long double> > A);

// TODO: Move this function to a better place
// FUnction to check for nans
template <typename Type>
bool is_nan(Type A) {
    return (A != A);
}

template <typename Type>
std::vector< Type > matrix_vector_mult(std::vector< std::vector<Type> > A) {
    // Define the vector
    std::vector<Type> C(A.size(),0);

    unsigned long m = A.size();

    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++)
        C[i] += A[i][j]*A[j][m];
    }

    return C;
}

template <typename Type>
std::vector< std::vector<Type> > matrix_mult(std::vector< std::vector<Type> > A, std::vector< std::vector<Type> > B) {
    // Define the vector
    std::vector< std::vector<Type> > C(A.size(), std::vector<Type> (B[0].size(), 0));

    unsigned long m = A.size();
    unsigned long n = A[0].size();
    unsigned long q = B[0].size();

    for(int i=0;i < m;++i) {
        for (int j = 0; j < q; ++j) {
            for (int k = 0; k < n; ++k)
                C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
        }
    }
    return C;
}


template <typename Type>
std::vector< std::vector<Type> > matrix_power(std::vector< std::vector<Type> > A, int n) {
    std::vector< std::vector<Type> > B = A;
    for(int i=0; i< n; i++) {
        B = matrix_mult(B, A);
    }
    return B;
}

#endif