#include "../../include/meta_optimization/pattern.hpp"

PatternSearch::PatternSearch(string file_name){
    seed_time();
    parse_param_file(file_name);
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
        cout << "\nBeginning Optimization Routine, fx = " << fx_best << endl;
    }

    while(current_iteration < max_iter){
        // This variable will keep track of whether or not an improvement has been made
        IMPROVED = false;
        if(verb) {
            cout << "\tIteration " << current_iteration + 1 << " of " << max_iter << endl;
        }
        for(int i=0; i<var_name.size(); i++){
            for(int j=1; j>-2; j-=2){
                // Modify the list of parameters
                p_current = p_best;
                new_val = var_vals[i] + j*step_sizes[i];
                // Keep it all in range
                if(new_val < lower_lims[i]){
                    new_val = lower_lims[i];
                }
                if(new_val > upper_lims[i]){
                    new_val = upper_lims[i];
                }
                if (verb) {
                    cout << "\t\tTrying " << var_name[i] << " = " << new_val << ", ";
                }
                p_current.set_from_pair(var_name[i], new_val);

                // Evalute the new combination
                MultipleTeams MTR(p_current);
                fx_current = MTR.solve();
                cout << "fx = " << fx_current << endl;

                // Keep track of the best solution
                if(fx_current < fx_best){
                    if (verb) {
                        cout << "\t\tImprovement." << endl;
                    }
                    var_vals[i] = new_val;
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
                cout << "\t\tUpdating stepsizes." << endl;
            }
            for(int i=0; i<step_sizes.size(); i++){
                step_sizes[i] /= 2.0;
            }
        }
        current_iteration++;
    }
}
