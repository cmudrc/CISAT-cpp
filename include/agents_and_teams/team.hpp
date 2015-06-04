#ifndef AGENTS_AND_TEAMS__TEAM_HPP
#define AGENTS_AND_TEAMS__TEAM_HPP

#include "agent.hpp"

class Team {
public:
    //// Functions
    Team(Parameters p);
    void solve(void);
    void new_start(void);
    void iterate(int iter);

    //// Variables
    Parameters p; // Parameters used for SA
    vector<Agent> agent_list;     // A vector to store agents in
    vector<long double> best_solution; // A vector to store the time-string of best solutions in

private:
    // nothing yet
};

#endif