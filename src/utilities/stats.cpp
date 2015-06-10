#include "../../include/utilities/stats.hpp"

//// Return the largest element in a vector.
long double vector_maximum(std::vector<long double> v){
    long double max = -LDBL_MAX;
    for(std::vector<long double>::iterator it = v.begin(); it != v.end(); ++it) {
        if(*it > max){
            max = *it;
        }
    }
    return max;
}

//// Returns the smallest element in a vector.
long double vector_minimum(std::vector<long double> v){
    long double min = LDBL_MAX;
    for(std::vector<long double>::iterator it = v.begin(); it != v.end(); ++it) {
        if(*it < min){
            min = *it;
        }
    }
    return min;
}


// Compute mean of a vector
long double mean(std::vector<long double> x) {
    return accumulate(x.begin(), x.end(), 0.0) / x.size();
}

// Compute mean of a deque
long double mean(std::deque<long double> x) {
    long double sum = 0;

    for(std::deque<long double>::iterator j=x.begin(); j!=x.end();++j){
        sum += *j;
    }

    return sum/x.size();
}

// Compute standard deviation of a vector
long double stdev(std::deque<long double> x) {
    long double mean_val = mean(x);
    long double s = 0;

    for(std::deque<long double>::iterator j=x.begin(); j!=x.end();++j){
        s += std::pow((*j - mean_val), 2.0);
    }

    return std::sqrt(s/x.size());
}

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

long double apply_weighting(std::vector<long double> a, std::vector<long double> b) {
    long double sum = 0;
    for (int i = 0; i < a.size(); i++) {
        sum += (a[i]*b[i]);
    }
    return sum;
}