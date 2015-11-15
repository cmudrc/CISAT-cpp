//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─utilities
//             ││      └─stats.cpp

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



// Function that returns the index of the maximum
long vector_argmax(std::vector<long double> v){
    long double max = -LDBL_MAX;
    long idx = -1;
    for(std::vector<long double>::iterator it = v.begin(); it != v.end(); ++it) {
        if(*it > max){
            max = *it;
            idx = (std::distance(v.begin(), it));
        }
    }
    return idx;
}


// Function that returns the index of the minimum value
long vector_argmin(std::vector<long double> v){
    long double min = LDBL_MAX;
    long idx = -1;
    for(std::vector<long double>::iterator it = v.begin(); it != v.end(); ++it) {
        if(*it < min){
            min = *it;
            idx = (std::distance(v.begin(), it));
        }
    }
    return idx;
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


// Compute standard deviation of a vector
long double stdev(std::vector<long double> x) {
    long double mean_val = mean(x);
    long double s = 0;

    for(std::vector<long double>::iterator j=x.begin(); j!=x.end();++j){
        s += std::pow((*j - mean_val), 2.0);
    }

    return std::sqrt(s/x.size());
}


// Applies a weighted sum to a vector
long double apply_weighting(std::vector<long double> a, std::vector<long double> b) {
    long double sum = 0;
    for (int i = 0; i < a.size(); i++) {
        sum += (a[i]*b[i]);
    }
    return sum;
}


// Computes cliff's delta for
long double pareto_cliff_delta(std::vector<std::vector<long double> > x, std::vector<std::vector<long double> > y) {
    unsigned long n = x.size();
    long double counter = 0;
    long double d = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            d = pareto_comparison(x[i], y[j]);
            if(d == 1){
                counter += 1;
            } else if (d == -1){
                counter -= 1;
            }
        }
    }
    return counter/(n*n);
}