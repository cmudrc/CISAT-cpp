#include "../../include/agent_team/team.hpp"

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
    for (int i=0; i < p.n_agents; i++){
        Agent().all_fx_current.push_back(0.0);
        Agent().all_xx_current.push_back(Solution());
    }

    // Give agents starting locations
    for(int i=0; i<p.n_agents; i++){
        agent_list[i].new_start();
    }

    // Save the first best solution
    best_solution[0] = vector_min(agent_list[0].all_fx_current);
};

//// Iterate the team
void Team::iterate(int iter){
    // Iterate each agent
    for(int i=0; i<agent_list.size(); i++){
        agent_list[i].iterate(iter);
    }

    // Share new results between agents
    for(int i=0; i<agent_list.size(); i++) {
        Agent().all_fx_current[agent_list[i].id] = agent_list[i].fx_current;
        Agent().all_xx_current[agent_list[i].id] = agent_list[i].x_current;
    }

    if (p.n_reps == 1){
        cout << endl;
    }
}


//// Solve the team
void Team::solve(void){
    // Iterate many times, and save the best solution each time
    for(int i=1; i<p.max_iter/p.n_agents; i++){
        // Do the iteration
        iterate(i);

        // Save the best solution
        best_solution[i] = vector_min(Agent().all_fx_current);

        // If it isn't better than last time, overwrite
        if(best_solution[i] > best_solution[i-1]){
            best_solution[i] = best_solution[i-1];
        }
    }
}
