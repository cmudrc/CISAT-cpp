#include "../../include/agents_and_teams/team.hpp"

//// This constructs the team
Team::Team(ParameterSet x){
    parameters = x;
    // Make a vector of the appropriate length for storing things.
    best_solution.assign(parameters.max_iter/parameters.n_agents, 0.0);
}

//// Give the team a new start
void Team::new_start(void){

    // If 
    if(agent_list.size() > 0){
        agent_list.clear();
    }

    // Create agent list
    for(int i=0; i< parameters.n_agents; i++){
        agent_list.emplace_back(Agent(i, parameters));
    }

    // Instantiate the sharing vectors for agents
    Agent::all_current_solutions.assign(parameters.n_agents, Solution());
    Agent::all_current_objective_weightings.assign(parameters.n_agents, std::vector<long double>(Solution::number_of_objectives));

    // Give agents starting locations
    for(int i=0; i< parameters.n_agents; i++){
        agent_list[i].new_start();
    }

    // Save the first best solution
    pull_best_solution(0);
};

//// Iterate the team
void Team::iterate(int iter){
    // Iterate each agent
    for(int i=0; i<agent_list.size(); i++){
        agent_list[i].iterate(iter);
    }

    // Share new results between agents
    for(int i=0; i<agent_list.size(); i++) {
        Agent::all_current_solutions[agent_list[i].agent_id] = agent_list[i].current_solution;
    }

    if (parameters.n_reps == 1){
        std::cout << std::endl;
    }

    // Pull out the best solution
    pull_best_solution(iter);
}


//// Solve the team
void Team::solve(void){
    // Iterate many times, and save the best solution each time
    for(int i=1; i< parameters.max_iter/ parameters.n_agents; i++){
        // Do the iteration
        iterate(i);
    }
}

void Team::pull_best_solution(int iter) {
    long double temp;
    unsigned long num = Solution::number_of_objectives;

    if(iter == 0) {
        best_solution[iter] = LDBL_MAX;
    } else {
        best_solution[iter] = best_solution[iter-1];
    }

    for(int i=0; i<agent_list.size(); i++) {
        temp = apply_weighting(agent_list[i].current_solution.quality, std::vector<long double> (num, 1.0/num));
        if (temp < best_solution[iter]) {
            best_solution[iter] = temp;
        }
    }
}
