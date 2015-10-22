//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  include
//  └─┴─────┘  ││   └─meta_optimization
//             ││      └─univariate.hpp

#ifndef META_OPTIMIZATION__UNIVARIATE_HPP
#define META_OPTIMIZATION__UNIVARIATE_HPP

#include "../agents_and_teams/multiple_teams.hpp"
#include "../utilities/optimization.hpp"
#include "search.hpp"

class UnivariateSearch : public Search {
public:
//// Functions
UnivariateSearch(std::string file_name); // A function to construct the thing.
void solve(int max_iter);  // A function to solve the problem.

//// Variables
int current_iteration;

private:
// nothing yet
};

#endif