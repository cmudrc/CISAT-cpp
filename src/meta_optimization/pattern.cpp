#include "../../include/meta_optimization/pattern.hpp"

PatternSearch::PatternSearch(std::string file_name){
    seed_time();
    parse_parameter_file(file_name);
}

void PatternSearch::solve(int max_iter, bool verb){
    // Do some initial things
    current_iteration = 0;
    long double fx_current;
    long double new_val;
    bool IMPROVED;
    Parameters p_current;

    // Find average initial quality
    MultipleTeams MT1(p_best);
    fx_best = MT1.solve();
    if(verb) {
        std::cout << "\nBeginning Optimization Routine, fx = " << fx_best << std::endl;
    }

    while(current_iteration < max_iter){
        // This variable will keep track of whether or not an improvement has been made
        IMPROVED = false;
        if(verb) {
            std::cout << "\tIteration " << current_iteration + 1 << " of " << max_iter << std::endl;
        }
        for(int i=0; i<variable_names.size(); i++){
            for(int j=1; j>-2; j-=2){
                // Modify the list of parameters
                p_current = p_best;
                new_val = variable_values[i] + j*step_sizes[i];
                // Keep it all in range
                if(new_val < lower_limits[i]){
                    new_val = lower_limits[i];
                }
                if(new_val > upper_limits[i]){
                    new_val = upper_limits[i];
                }
                if (verb) {
                    std::cout << "\t\tTrying " << variable_names[i] << " = " << new_val << ", ";
                }
                p_current.set_from_pair(variable_names[i], new_val);

                // Evalute the new combination
                MultipleTeams MTR(p_current);
                fx_current = MTR.solve();
                std::cout << "fx = " << fx_current << std::endl;

                // Keep track of the best solution
                if(fx_current < fx_best){
                    if (verb) {
                        std::cout << "\t\tImprovement." << std::endl;
                    }
                    variable_values[i] = new_val;
                    fx_best = fx_current;
                    p_best = p_current;
                    IMPROVED = true;
                    i = 100000;
                    j = -100000;
                }
            }
        }

        // If no improvement, update the stepsize values
        if(!IMPROVED){
            if (verb) {
                std::cout << "\t\tUpdating stepsizes." << std::endl;
            }
            for(int i=0; i<step_sizes.size(); i++){
                step_sizes[i] /= 2.0;
            }
        }
        current_iteration++;
    }
}
