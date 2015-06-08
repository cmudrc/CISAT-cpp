#include "../../include/agents_and_teams/team.hpp"

//// This constructs the team
Team::Team(Parameters x){
    p = x;
    // Make a vector of the appropriate length for storing things.
    best_solution.assign(p.max_iter/p.n_agents, 0.0);
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
    Agent::quality_of_all_current_solutions.assign(p.n_agents, 0.0);
    Agent::all_current_solutions.assign(p.n_agents, Solution());
    Agent::all_current_objective_weightings.assign(p.n_agents, std::vector<long double>(static_cast <unsigned long> (Solution::number_of_objectives), 0.0));

    // Give agents starting locations
    for(int i=0; i<p.n_agents; i++){
        agent_list[i].new_start();
    }

    // Save the first best solution
    best_solution[0] = vector_min(Agent::quality_of_all_current_solutions);
};

//// Iterate the team
void Team::iterate(int iter){
    // Iterate each agent
    for(int i=0; i<agent_list.size(); i++){
        agent_list[i].iterate(iter);
    }

    // Share new results between agents
    for(int i=0; i<agent_list.size(); i++) {
        Agent::quality_of_all_current_solutions[agent_list[i].agent_id] = agent_list[i].fx_current;
        Agent::all_current_solutions[agent_list[i].agent_id] = agent_list[i].x_current;
    }

    if (p.n_reps == 1){
        std::cout << std::endl;
    }
}


//// Solve the team
void Team::solve(void){
    // Iterate many times, and save the best solution each time
    for(int i=1; i<p.max_iter/p.n_agents; i++){
        // Do the iteration
        iterate(i);

        // Save the best solution
        best_solution[i] = vector_min(Agent::quality_of_all_current_solutions);

        // If it isn't better than last time, overwrite
        if(best_solution[i] > best_solution[i-1]){
            best_solution[i] = best_solution[i-1];
        }
    }
}
