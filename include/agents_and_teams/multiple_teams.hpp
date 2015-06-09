#ifndef AGENTS_AND_TEAMS__MULTIPLE_TEAMS_HPP
#define AGENTS_AND_TEAMS__MULTIPLE_TEAMS_HPP

#include "team.hpp"
#include <algorithm>

class MultipleTeams {
public:
    //// Functions
    MultipleTeams(ParameterSet x); // A function to construct the thing from an object
    MultipleTeams(std::string file_name); // A function to construct the thing from file
    long double solve(void);  // A function to solve the problem.

    //// Variables
    ParameterSet parameters;       // The parameters of the simulation
    std::vector< std::vector<long double > > best_solution; // Stores the string of best values from every run.
    std::vector<long double> cdf;

private:
    // nothing yet
};

#endif
