//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  include
//  └─┴─────┘  ││   └─meta_optimization
//             ││      └─pattern.hpp

#ifndef META_OPTIMIZATION__PATTERN_HPP
#define META_OPTIMIZATION__PATTERN_HPP

#include "../agents_and_teams/multiple_teams.hpp"
#include "search.hpp"

class PatternSearch : public Search {
public:
    //// Functions
    PatternSearch(std::string file_name); // A function to construct the thing.
    void solve(int max_iter);  // A function to solve the problem.

    //// Variables
    int current_iteration;
    long double fx_best;

private:
    // nothing yet
};

#endif