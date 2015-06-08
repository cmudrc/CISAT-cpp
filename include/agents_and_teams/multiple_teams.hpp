#ifndef AGENTS_AND_TEAMS__MULTIPLE_TEAMS_HPP
#define AGENTS_AND_TEAMS__MULTIPLE_TEAMS_HPP

#include "team.hpp"
#include <algorithm>

class MultipleTeams {
public:
    //// Functions
    MultipleTeams(Parameters x); // A function to construct the thing from an object
    MultipleTeams(std::string file_name); // A function to construct the thing from file
    long double solve(void);  // A function to solve the problem.

    //// Variables
    Parameters p;       // The parameters of the simulation
    std::vector<long double> cdf; // Stores the best value found in every run
    std::vector< std::vector<long double> > best_solution; // Stores the string of best values from every run.

private:
    // nothing yet
};

#endif
