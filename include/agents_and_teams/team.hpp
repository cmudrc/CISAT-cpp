//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  include
//  └─┴─────┘  ││   └─agents_and_teams
//             ││      └─team.hpp

#ifndef AGENTS_AND_TEAMS__TEAM_HPP
#define AGENTS_AND_TEAMS__TEAM_HPP

#include "agent.hpp"

class Team {
public:
    //// Functions
    Team(ParameterSet x);
    void solve(void);
    void new_start(void);
    void iterate(int iter);
    void pull_best_solution(int iter);

    //// Variables
    ParameterSet parameters; // ParameterSet used for SA
    std::vector<Agent> agent_list;     // A vector to store agents in
    std::vector<long double> best_solution; // A vector to store the time-string of best solutions in

private:
    // nothing yet
    unsigned long team_id;
};

#endif