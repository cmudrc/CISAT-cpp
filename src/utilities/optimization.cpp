#include "../../include/utilities/optimization.hpp"

// Compute the x value fo the optimum of a linear regression
std::vector<long double> quad_max(std::vector<long double> x, std::vector<long double> y){

    // Initialize things
    std::vector< std::vector<long double> > A(3, std::vector<long double>(4, 0.0));
    std::vector<long double> xx;
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
    long double x_min = vector_minimum(x);
    long double x_max = vector_maximum(x);

    // Check to make sure the equation is concave up
    if(xx[2] > 0){
        x_loc = -xx[1]/(2*xx[2]);
    } else {
        if ((xx[0] + x_min*xx[1] +x_min*x_min*xx[2]) > (xx[0] + x_max*xx[1] +x_max*x_max*xx[2]) ) {
            x_loc = x_max;
        } else {
            x_loc = x_min;
        }
    }

    // Check to make sure the solution is in the trust region
    x_loc = std::min(x_loc, x_max);
    x_loc = std::max(x_loc, x_min);

    // Compute the r-squared value
    long double sse_mean = 0;
    long double sse_reg = 0;
    long double my = mean(y);
    for(int i=0; i < y.size(); i++){
        sse_mean += std::pow(y[i] - my, 2);
        sse_reg  += std::pow(xx[0] + x[i]*xx[1] +x[i]*x[i]*xx[2] - y[i], 2);
    }

    std::vector<long double> results;
    results.push_back(x_loc);
    results.push_back(xx[0] + x_loc*xx[1] +x_loc*x_loc*xx[2]);
    results.push_back(my);
    results.push_back(1.0 - sse_reg/sse_mean);

    return results;

}

// Computes the pareto front for a set of data
std::vector<bool> get_pareto_front(std::vector< std::vector<long double> > y){
    std::vector<bool> is_pareto(y.size(), true);
    int counter = 0;

    for(int i=0; i<y.size(); i++) {
        for (int j=0; j<y.size(); j++) {
            // Reset the counter
            counter = 0;

            // Compare points i and j on every criteria
            for (int k=0; k<y[0].size(); k++) {
                if (y[i][k] >= y[j][k]) {
                    counter++;
                }
            }

            // If point j is better than point i for all criteria, remove point i from pareto
            if (counter == y[0].size()) {
                is_pareto[i] = false;
                break;
            }
        }
    }

    return is_pareto;
}

// Returns the pareto tiers for a data set
std::vector<int> get_pareto_tiers(std::vector< std::vector<long double> > y){
    // Make a vector to save tiers
    std::vector<int> tiers(y.size(), 0);
    std::vector<bool> is_pareto(y.size(), false);
    std::vector<long double> replacement(y[0].size(), LDBL_MAX);
    int pareto_counter = 0;
    int tier_counter = 0;

    //
    while (pareto_counter != y.size()) {
        // Get the current tier
        is_pareto = get_pareto_front(y);
        tier_counter++;

        for (int i =0; i < y.size(); i++) {
            if (is_pareto[i]){
                y[i] = replacement;
                tiers[i] = tier_counter;
                pareto_counter++;
            }
        }
    }
    return tiers;
}