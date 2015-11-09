//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─agents_and_teams
//             ││      └─team.cpp

#include "../../include/agents_and_teams/team.hpp"

//// This constructs the team
Team::Team(ParameterSet x){
    parameters = x;
    // Make a vector of the appropriate length for storing things.
    best_solution.assign(Solution::number_of_objectives, std::vector<long double> (parameters.max_iter/parameters.n_agents, 0.0));
}

//// Give the team a new start
void Team::new_start(void){
    if(parameters.save_designs >=1){
        // Make a new folder for team results
        char directory_name[50];
        std::sprintf(directory_name, "./data/%lu/t%03d", run_id, team_id);
        mkdir(directory_name, ACCESSPERMS);

        // Make a subdirectory for every agent
        for(int i=0; i<parameters.n_agents; i++){
            char sub_directory_name[50];
            std::sprintf(sub_directory_name, "./data/%lu/t%03d/a%03d/", run_id, team_id, i);
            mkdir(sub_directory_name, ACCESSPERMS);
        }
    }

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
void Team::iterate(int iteration){
    // Iterate each agentf
    for(int i=0; i<agent_list.size(); i++){
        agent_list[i].iterate(iteration);
    }

    // Share new results between agents
    for(int i=0; i<agent_list.size(); i++) {
        Agent::all_current_solutions[agent_list[i].agent_id] = agent_list[i].current_solution;
    }

    if (parameters.n_reps == 1){
        std::cout << std::endl;
    }

    // Pull out the best solution
    pull_best_solution(iteration);
}


//// Solve the team
void Team::solve(void){
    // Iterate many times, and save the best solution each time
    for(int i=1; i< parameters.max_iter/ parameters.n_agents; i++){
        // Do the iteration
        iterate(i);
    }

    // Save best
    int iter = static_cast<int> (parameters.max_iter/ parameters.n_agents - 1);
    for (int i = 0; i < agent_list.size(); i++) {
        if(parameters.save_designs == 1) {
            char buff[50];
            std::sprintf(buff, "./data/%lu/t%03d/a%03d/d%08d.html", run_id, team_id, i, iter);
            std::string name(buff);
            agent_list[i].current_solution.save_as_x3d(name);
        }
    }
}

void Team::pull_best_solution(int iteration) {
    long double temp;
    unsigned long num = Solution::number_of_objectives;

    for(int i=0; i<Solution::number_of_objectives; i++) {
        if (iteration == 0) {
            best_solution[i][iteration] = LDBL_MAX;
        } else {
            best_solution[i][iteration] = best_solution[i][iteration - 1];
        }
    }

    for (int i = 0; i < agent_list.size(); i++) {
        if(parameters.save_designs == 2) {
            char buff[50];
            std::sprintf(buff, "./data/%lu/t%03d/a%03d/d%08d.html", run_id, team_id, i, iteration);
            std::string name(buff);
            agent_list[i].current_solution.save_as_x3d(name);
        }

        // Make vectors for comparison
        std::vector<long double> x(Solution::number_of_objectives), y(Solution::number_of_objectives);
        for(int j=0; j<Solution::number_of_objectives; j++) {
            x[j] = agent_list[i].current_solution.quality[j];
            y[j] = best_solution[j][iteration];
        }

        // Compare vectors
        if (pareto_comparison(x, y) > 0) {
            for(int j=0; j<Solution::number_of_objectives; j++) {
                best_solution[j][iteration] = x[j];
            }
        }
    }
}
