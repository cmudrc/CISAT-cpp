#ifndef META_OPTIMIZATION__UNIVARIATE_HPP
#define META_OPTIMIZATION__UNIVARIATE_HPP

#include "../agents_and_teams/multiple_teams.hpp"
#include "search.hpp"

using namespace std;

class UnivariateSearch : public Search {
public:
//// Functions
UnivariateSearch(string file_name); // A function to construct the thing.
void solve(int max_iter, bool verb);  // A function to solve the problem.

//// Variables
int current_iteration;

private:
// nothing yet
};

#endif