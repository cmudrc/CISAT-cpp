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


long double apply_weighting(std::vector<long double> a, std::vector<long double> b) {
    long double sum = 0;
    for (int i = 0; i < a.size(); i++) {
        sum += (a[i]*b[i]);
    }
    return sum;
}