#include "../../include/agents_and_teams/team.hpp"

//// This constructs the team
Team::Team(ParameterSet x){
    p = x;
    // Make a vector of the appropriate length for storing things.
    best_solution.assign(p.max_iter/p.n_agents,
                         std::vector<long double>(static_cast <unsigned long> (Solution::number_of_objectives, 0.0)));
}

//// Give the team a new start
void Team::new_start(void){

    // If 
    if(agent_list.size() > 0){
        agent_list.clear();
    }

    // Create agent list
    for(int i=0; i<p.n_agents; i++){
        agent_list.emplace_back(Agent(i, p));
    }

    // Instantiate the sharing vectors for agents
    Agent::all_current_solutions.assign(p.n_agents, Solution());
    Agent::all_current_objective_weightings.assign(p.n_agents, std::vector<long double>(static_cast <unsigned long> (Solution::number_of_objectives), 0.0));

    // Give agents starting locations
    for(int i=0; i<p.n_agents; i++){
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

    if (p.n_reps == 1){
        std::cout << std::endl;
    }

    // Pull out the best solution
    pull_best_solution(iter);
}


//// Solve the team
void Team::solve(void){
    // Iterate many times, and save the best solution each time
    for(int i=1; i<p.max_iter/p.n_agents; i++){
        // Do the iteration
        iterate(i);
    }
}

#include "../../include/utilities/custom_print.hpp"

void Team::pull_best_solution(int iter) {
    // If a solution is good, add it to the pareto set with a stamp
    std::vector<long double> temp;
    if(iter == 0) {
        temp.assign(Solution::number_of_objectives, LDBL_MAX);
    } else {
        temp = best_solution[iter-1];
    }
    for(int i=0; i<p.n_agents; i++) {
        for (int j=0; j < Solution::number_of_objectives; j++){
            if (agent_list[i].current_solution.quality[j] < temp[j]) {
                temp[j] = agent_list[i].current_solution.quality[j];
            }
        }
    }
    best_solution[iter] = temp;
}
