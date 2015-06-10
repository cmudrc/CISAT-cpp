#include "../../include/agents_and_teams/agent.hpp"

//// Necessary definitions of static vectors for sharing between agents.
std::vector<Solution> Agent::all_current_solutions;
std::vector< std::vector<long double> > Agent::all_current_objective_weightings;

//// Normal agent constructor, take one int
Agent::Agent(int ID, ParameterSet x){
    // Save the list of parameters
    parameters = x;

    // Remember your damn name, agent
    agent_id = ID;

    // The beginning is usually the best place to start
    iteration_number = 0;

    // Set initial temperature
    triki_temperature = parameters.initial_temperature;
    temperature = parameters.initial_temperature;
}

//// A function that selects a random starting point, and pushes it to other agents.
void Agent::new_start(void){
    // Define initial move operator preferences
    move_oper_pref.assign(Solution::number_of_move_ops, 1.0);

    // Define objective weighting
    objective_weighting.assign(Solution::number_of_objectives, 1.0);
    all_current_objective_weightings[agent_id] = objective_weighting;

    // Select a random starting point and evaluate it
    current_solution = Solution();
    current_solution_quality = apply_weighting(current_solution.quality, objective_weighting);
    best_solution_so_far = current_solution_quality;

    // Share the information
    all_current_solutions[agent_id] = current_solution;
}

//// Generated a candidate solution using Cauchy distribution.
Solution Agent::candidate_solution(void){
    // Make some variable for use in this function
    Solution candidate; // stores the candidate solution
    std::vector<long double> w(parameters.n_agents, 0.0);         // Vector of weights across agents
    long double wmax;              // Maximum in weight vector
    long double sum_w = 0;
    long double old_fx = 0, new_fx = 0;
    int j;                    // Index for random draw


    // If a random draw is lower than teh probability of interaction, then interact.
    if(parameters.interaction > uniform(1.0, 0.0)) {
        // Build the weight vector
        for(int i=0; i < parameters.n_agents; i++) {
            w[i] = apply_weighting(all_current_solutions[i].quality, objective_weighting);
        }
        wmax = vector_maximum(w);

        // Make a thing
        for (int i = 0; i < w.size(); i++) {
            w[i] = wmax - w[i];
            sum_w += w[i];
        }
        
        // Normalize the thing, and incorporate self-bias and quality-bias
        for (int i = 0; i < w.size(); i++) {
            w[i] /= sum_w;
            w[i] += parameters.q_bias;
        }
        w[agent_id] += parameters.s_bias;

        j = weighted_choice(w);
        candidate = all_current_solutions[j];
    } else{
        candidate = current_solution;
    }

    // Choose which move operator to apply
    j = weighted_choice(move_oper_pref);

    // [1] Save current quality, [2] apply move operator, [3] check new quality
    // [1]
    old_fx = apply_weighting(candidate.quality, objective_weighting);
    // [2]
    candidate.get_valid_moves();
    candidate.apply_move_operator(uniform_int(static_cast <int> (candidate.move_options.size()-1), 0));
    // [3]
    new_fx = apply_weighting(candidate.quality, objective_weighting);

    // Update move operator preferences
    if (new_fx < old_fx) {
        move_oper_pref[j] *= (1 + parameters.op_learn);
    } else if (new_fx > old_fx) {
        move_oper_pref[j] *= (1 - parameters.op_learn);
    }

    // Normalize the vector so it doesn't get out of hand
    sum_w = 0;
    for (int i=0; i < move_oper_pref.size(); i++) {
        sum_w += move_oper_pref[i];
    }
    for (int i=0; i < move_oper_pref.size(); i++) {
        move_oper_pref[i]/=sum_w;
    }

    return candidate;

}

//// A function to perform an iteration of SA.
void Agent::iterate(int iter){

    // Save the god-given iteration as the current iteration
    iteration_number = iter;

    // Vector for saving new candidate solution
    Solution x_cand;

    // Objective function value of current solution, and probability of accepting new solution
    long double fx_cand, p_accept;

    // Generate a new solution
    x_cand = candidate_solution();
    fx_cand = apply_weighting(x_cand.quality, objective_weighting);

    if(parameters.history_length < 0) {
        history.push_back(fx_cand);
    }

    // If it is better, accept it
    if(fx_cand < current_solution_quality){
        // Save locally
        current_solution = x_cand;
        current_solution_quality = fx_cand;
    } else {
        // If not, accept with some probability
        p_accept = std::exp((current_solution_quality - fx_cand)/temperature);
        if(uniform(1.0, 0.0) < p_accept){
            // Save locally
            current_solution = x_cand;
            current_solution_quality = fx_cand;
        }
    }

    // Update best so far
    if (current_solution_quality < best_solution_so_far) {
        best_solution_so_far = current_solution_quality;
    }

    if(parameters.history_length > 0) {
        history.push_back(current_solution_quality);
    }

    //Update the temperature
    update_temp();
}

//// Updates temperature using simple stretched Cauchy schedule.
void Agent::update_temp(void) {

    if(parameters.n_reps == 1)
        std::cout << temperature << ", ";

    // If history_length is greater than 0, use a sliding window for the update
    if(parameters.history_length > 0) {
        // If the quality history is too long, pop one out and calculate the update
        if (history.size() > parameters.history_length) {
            history.pop_front();
            triki_temperature = update_triki();

            temperature = parameters.satisficing_fraction* parameters.initial_temperature*(std::max(static_cast <long double> (0.0),
                                                                  best_solution_so_far - Solution::goal)/
                                                                        best_solution_so_far)
                          + (1.0- parameters.satisficing_fraction)*triki_temperature;
        }
    }

    // If history length is less than 0, use an absolute stepping scheme
    if(parameters.history_length < 0) {
        bool update = false;

        // See if its time to compute an update
        if(iteration_number % parameters.history_length == 0) {
            update = true;
        }

        // If adaptive and time to update, update triki and clear the cache
        if(update){
            triki_temperature = update_triki();
            temperature = parameters.satisficing_fraction* parameters.initial_temperature*(std::max(static_cast <long double> (0.0),
                                                                            best_solution_so_far - Solution::goal)/
                                                                        best_solution_so_far)
                          + (1.0- parameters.satisficing_fraction)*triki_temperature;

            history.clear();
        }
    }
}


// This function updates Triki
long double Agent::update_triki(void){
    long double q_std = stdev(history);
    long double update_factor = parameters.delt * triki_temperature / std::pow(q_std, 2);
    if (q_std > 0.0) {
        if (update_factor > 1.0) {
            // Update delt and update_factor
            parameters.delt /= 2.0;
            update_factor /= 2.0;
        }
        if(update_factor > 1.0){
            return triki_temperature;
        } else {
            return triki_temperature * (1.0 - update_factor);
        }

    } else {
        return triki_temperature;
    }
}