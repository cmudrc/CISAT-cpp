#include "../../include/utilities/matrix_operations.hpp"

std::vector<long double> gauss(std::vector< std::vector<long double> > A) {
    // From http://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/

    int n = static_cast <int> (A.size());

    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        long double maxEl = std::abs(A[i][i]);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (std::abs(A[k][i]) > maxEl) {
                maxEl = std::abs(A[k][i]);
                maxRow = k;
            }
        }

        // Swap maximum row with current row (column by column)
        for (int k=i; k<n+1;k++) {
            long double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int k=i+1; k<n; k++) {
            long double c = -A[k][i]/A[i][i];
            for (int j=i; j<n+1; j++) {
                if (i==j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    std::vector<long double> x(static_cast <unsigned long> (n));
    for (int i=n-1; i>=0; i--) {
        x[i] = A[i][n]/A[i][i];
        for (int k=i-1;k>=0; k--) {
            A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;
}