#include "../../include/agents_and_teams/multiple_teams.hpp"

using namespace std;

// This does the things, and initializes p from file
MultipleTeams::MultipleTeams(ParameterSet x){
    // Save the parameters
    p = x;

    // Initialize the best solution vector
    best_solution.assign(p.n_reps,
                         std::vector< std::vector<long double> > (p.max_iter,
                         std::vector<long double>(static_cast <unsigned long> (Solution::number_of_objectives, 0.0))));
}

// This does the things, and initializes p from file
MultipleTeams::MultipleTeams(string file_name){
    // Read from a file
    p.set_from_file(file_name);

    // Initialize the best solution vector
    best_solution.assign(p.n_reps,
                         std::vector< std::vector<long double> > (p.max_iter/p.n_agents,
                         std::vector<long double>(static_cast <unsigned long> (Solution::number_of_objectives, 0.0))));
}

//// This actually solves the problem LOTS of times.
long double MultipleTeams::solve(void){

    for(int i = 0; i<p.n_reps; i++) {
        // Instantiate a new team
        Team T(p);

        // Give the team a new start
        T.new_start();

        // Solve the problem with the team
        T.solve();

        // Save results
        best_solution[i] = T.best_solution;
    }
}
