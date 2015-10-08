//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─agents_and_teams
//             ││      └─multiple_teams.cpp

#include "../../include/agents_and_teams/multiple_teams.hpp"

// This does the things, and initializes parameters from file
MultipleTeams::MultipleTeams(ParameterSet x){
    // Save the parameters
    parameters = x;

    // Initialize the best solution vector
    best_solution.assign(parameters.n_reps, std::vector<long double> (parameters.max_iter/parameters.n_agents, 0.0));
}

// This does the things, and initializes parameters from file
MultipleTeams::MultipleTeams(std::string file_name){
    // Read from a file
    parameters.set_from_file(file_name);

    // Initialize the best solution vector
    best_solution.assign(parameters.n_reps, std::vector<long double> (parameters.max_iter/parameters.n_agents, 0.0));
}

//// This actually solves the problem LOTS of times.
long double MultipleTeams::solve(void){

    for(int i = 0; i< parameters.n_reps; i++) {
        // Instantiate a new team
        Team this_team(parameters);

        // Give the team a new start
        this_team.new_start();

        // Solve the problem with the team
        this_team.solve();

        // Save results
        best_solution[i] = this_team.best_solution;
        cdf.push_back(this_team.best_solution.back());
    }

    std::sort(cdf.begin(), cdf.end());

    return mean(cdf);
}
