#include "../../include/agents_and_teams/agent.hpp"

//// Necessary definitions of static vectors for sharing between agents.
std::vector<long double> Agent::quality_of_all_current_solutions;
std::vector<Solution> Agent::all_current_solutions;
std::vector< std::vector<long double> > Agent::all_current_objective_weightings;

//// Inline Agent constructor for accessing static vectors
Agent::Agent(void){}

//// Normal agent constructor, take one int
Agent::Agent(int ID, Parameters x){
    // Save the list of parameters
    p = x;

    // Remember your damn name, agent
    agent_id = ID;

    // The beginning is usually the best place to start
    iteration_number = 0;

    // Set initial temperature
    triki_temperature = p.initial_temperature;
    temperature = p.initial_temperature;

    // Define initial move operator preferences
    move_oper_pref.assign(static_cast <unsigned long> (x_current.number_of_move_ops), 1.0);

    // Define objective weighting
    objective_weighting.assign(static_cast <unsigned long> (Solution(false).number_of_objectives), 1.0);
    print(objective_weighting);
    all_current_objective_weightings[agent_id] = objective_weighting;
}

//// A function that selects a random starting point, and pushes it to other agents.
void Agent::new_start(void){

    // Select a random starting point and evaluate it
    x_current = Solution();
    fx_current = apply_weighting(x_current.quality, objective_weighting);
    best_so_far = fx_current;

    // Share the information
    quality_of_all_current_solutions[agent_id] = fx_current;
    all_current_solutions[agent_id] = x_current;
}

//// Generated a candidate solution using Cauchy distribution.
Solution Agent::candidate_solution(void){
    // Make some variable for use in this function
    Solution candidate; // stores the candidate solution
    std::vector<long double> w;         // Vector of weights across agents
    long double wmax;              // Maximum in weight vector
    long double sum_w = 0;
    long double old_fx = 0, new_fx = 0;
    int j;                    // Index for random draw


    // If a random draw is lower than teh probability of interaction, then interact.
    if(p.interaction > uniform(1.0, 0.0)) {
        w = quality_of_all_current_solutions;
        wmax = vector_max(w);

        // Make a thing
        for (int i = 0; i < w.size(); i++) {
            w[i] = wmax - w[i];
            sum_w += w[i];
        }
        
        // Normalize the thing, and incorporate self-bias and quality-bias
        for (int i = 0; i < w.size(); i++) {
            w[i] /= sum_w;
            w[i] += p.q_bias;
        }
        w[agent_id] += p.s_bias;

        j = weighted_choice(w);
        candidate = all_current_solutions[j];
    } else{
        candidate = x_current;
    }

    // Choose which move operator to apply
    j = weighted_choice(move_oper_pref);

    // Save current quality, apply move operator
    old_fx = apply_weighting(candidate.quality, objective_weighting);
    candidate.apply_move_operator(j, temperature);
    new_fx = apply_weighting(candidate.quality, objective_weighting);

    // Update move operator preferences
    if (new_fx < old_fx) {
        move_oper_pref[j] *= (1 + p.op_learn);
    } else if (new_fx > old_fx) {
        move_oper_pref[j] *= (1 - p.op_learn);
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

    if(p.history_length < 0) {
        history.push_back(fx_cand);
    }

    // If it is better, accept it
    if(fx_cand < fx_current){
        // Save locally
        x_current = x_cand;
        fx_current = fx_cand;
    } else {
        // If not, accept with some probability
        p_accept = exp((fx_current - fx_cand)/temperature);
        if(uniform(0.0, 1.0) < p_accept){
            // Save locally
            x_current = x_cand;
            fx_current = fx_cand;
        }
    }

    // Update best so far
    if (fx_current < best_so_far) {
        best_so_far = fx_current;
    }

    if(p.history_length > 0) {
        history.push_back(fx_current);
    }

    //Update the temperature
    update_temp();
}

//// Updates temperature using simple stretched Cauchy schedule.
void Agent::update_temp(void) {

    if(p.n_reps == 1)
        std::cout << temperature << ", ";

    // If history_length is greater than 0, use a sliding window for the update
    if(p.history_length > 0) {
        // If the quality history is too long, pop one out and calculate the update
        if (history.size() > p.history_length) {
            history.pop_front();
            triki_temperature = update_triki();

            temperature = p.satisficing_fraction*p.initial_temperature*(std::max(static_cast <long double> (0.0),
                                                                  best_so_far - Solution(false).goal)/best_so_far)
                          + (1.0-p.satisficing_fraction)*triki_temperature;
        }
    }

    // If history length is less than 0, use an absolute stepping scheme
    if(p.history_length < 0) {
        bool update = false;

        // See if its time to compute an update
        if(iteration_number % p.history_length == 0) {
            update = true;
        }

        // If adaptive and time to update, update triki and clear the cache
        if(update){
            triki_temperature = update_triki();
            temperature = p.satisficing_fraction*p.initial_temperature*(std::max(static_cast <long double> (0.0),
                                                                            best_so_far - Solution(false).goal)/best_so_far)
                          + (1.0-p.satisficing_fraction)*triki_temperature;

            history.clear();
        }
    }
}


// This function updates Triki
long double Agent::update_triki(void){
    long double q_std = stdev(history);
    long double update_factor = p.delt * triki_temperature / pow(q_std, 2);
    if (q_std > 0.0) {
        if (update_factor > 1.0) {
            // Update delt and update_factor
            p.delt /= 2.0;
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