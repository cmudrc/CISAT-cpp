#include "../../include/utilities/stats.hpp"

//// Return the largest element in a vector.
long double vector_max(vector<long double> v){
    long double max = -DBL_MAX;
    for(vector<long double>::iterator it = v.begin(); it != v.end(); ++it) {
        if(*it > max){
            max = *it;
        }
    }
    return max;
}

//// Returns the smallest element in a vector.
long double vector_min(vector<long double> v){
    long double min = DBL_MAX;
    for(vector<long double>::iterator it = v.begin(); it != v.end(); ++it) {
        if(*it < min){
            min = *it;
        }
    }
    return min;
}


// Compute mean of a vector
long double mean(vector<long double> x) {
    return accumulate(x.begin(), x.end(), 0.0) / x.size();
}

// Compute mean of a deque
long double mean(deque<long double> x) {
    long double sum = 0;

    for(deque<long double>::iterator j=x.begin(); j!=x.end();++j){
        sum += *j;
    }

    return sum/x.size();
}

// Compute standard deviation of a vector
long double stdev(deque<long double> x) {
    long double mean_val = mean(x);
    long double s = 0;

    for(deque<long double>::iterator j=x.begin(); j!=x.end();++j){
        s += pow((*j - mean_val), 2.0);
    }

    return sqrt(s/x.size());
}

// Compute the x value fo the optimium of a linear regression
vector<long double> quad_max(vector<long double> x, vector<long double> y){

    // Initialize things
    vector< vector<long double> > A(3, vector<long double>(4, 0.0));
    vector<long double> xx;
    long double n   = 0.0;
    long double x1  = 0.0;
    long double x2  = 0.0;
    long double x3  = 0.0;
    long double x4  = 0.0;
    long double y1  = 0.0;
    long double yx1 = 0.0;
    long double yx2 = 0.0;

    // Calculate some sums that will be necessary
    for(int i=0; i < x.size(); i++) {
        n   += 1;
        x1  += x[i];
        x2  += x[i]*x[i];
        x3  += x[i]*x[i]*x[i];
        x4  += x[i]*x[i]*x[i]*x[i];
        y1  += y[i];
        yx1 += y[i]*x[i];
        yx2 += y[i]*x[i]*x[i];
    }

    // Make a matrix
    A[0][0] = n;
    A[1][0] = x1;
    A[0][1] = x1;
    A[0][2] = x2;
    A[1][1] = x2;
    A[2][0] = x2;
    A[1][2] = x3;
    A[2][1] = x3;
    A[2][2] = x4;
    A[0][3] = y1;
    A[1][3] = yx1;
    A[2][3] = yx2;

    xx = gauss(A);

    long double x_loc;
    long double x_min = vector_min(x);
    long double x_max = vector_max(x);

    // Check to make sure the equation is concave up
    if(xx[2] > 0){
        x_loc = -xx[1]/(2*xx[2]);
    } else {

        if ((xx[0] + x_min*xx[1] +x_min*x_min*xx[2]) >
                (xx[0] + x_max*xx[1] +x_max*x_max*xx[2]) ) {
            x_loc = x_max;
        } else {
            x_loc = x_min;
        }
    }

    // Check to make sure the solution is in teh trust region
    x_loc = min(x_loc, x_max);
    x_loc = max(x_loc, x_min);

    // Compute the r-squared value
    long double sse_mean = 0;
    long double sse_reg = 0;
    long double my = mean(y);
    for(int i=0; i < y.size(); i++){
        sse_mean += pow(y[i] - my, 2);
        sse_reg  += pow(xx[0] + x[i]*xx[1] +x[i]*x[i]*xx[2] - y[i], 2);
    }

    vector<long double> results;
    results.push_back(x_loc);
    results.push_back(xx[0] + x_loc*xx[1] +x_loc*x_loc*xx[2]);
    results.push_back(my);
    results.push_back(1.0 - sse_reg/sse_mean);

    return results;

}

vector<long double> gauss(vector< vector<long double> > A) {
    // From http://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/

    int n = static_cast <int> (A.size());

    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        long double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
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
    vector<long double> x(static_cast <unsigned long> (n));
    for (int i=n-1; i>=0; i--) {
        x[i] = A[i][n]/A[i][i];
        for (int k=i-1;k>=0; k--) {
            A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;
}