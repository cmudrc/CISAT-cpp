#ifndef PATTERN_HPP
#define PATTERN_HPP

#include "../agent_team/multipleteams.hpp"
#include "search.hpp"

using namespace std;

class PatternSearch : public Search {
public:
    //// Functions
    PatternSearch(string file_name); // A function to construct the thing.
    void solve(int max_iter, bool verb);  // A function to solve the problem.

    //// Variables
    int current_iteration;
    long double fx_best;

private:
    // nothing yet
};

#endif