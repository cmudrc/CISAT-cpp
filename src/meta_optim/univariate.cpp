#include "../../include/meta_optim/univariate.hpp"

UnivariateSearch::UnivariateSearch(string file_name){
    seed_time();
    parse_param_file(file_name);
}

void UnivariateSearch::solve(int max_iter, bool verb){
    // Stores the current iteration and values
    current_iteration = 0;
    Parameters p_current;

    // Stores a new value
    long double new_val = 0;

    // Keeps track of whether or not an edge solution has been found
    bool EDGE_SOLUTION;

    // Keeps track of whether a bound is being approached
    bool APPROACHING_BOUND;

    // Stores values to feed to quadratic regression
    vector<long double> X(p_best.n_reps, 0.0);
    vector<long double> Y(p_best.n_reps, 0.0);

    // Stores the results from the quadratic regression
    vector<long double> quad_res;
    long double temp_ub;
    long double temp_lb;
    if(verb) {
        cout << "\nBeginning Optimization Routine" << endl;
    }

    // Do some iterations, bro. Get mad optimized.
    while(current_iteration < max_iter) {
        if(verb) {
            cout << "\tIteration " << current_iteration + 1 << " of " << max_iter << endl;
        }
        EDGE_SOLUTION = false;
        APPROACHING_BOUND = false;
        // Within each iteration, step in each direction
        for (int i = 0; i < var_name.size(); i++) {
            if(verb) {
                cout << "\t\tComputing " << var_name[i];
            }

            // Draw a random variable in the param range
            temp_ub = min(var_vals[i]+step_sizes[i], upper_lims[i]);
            temp_lb = max(var_vals[i]-step_sizes[i], lower_lims[i]);

            // Check to see if we're up against a bound
            if(temp_ub == upper_lims[i] || temp_lb == lower_lims[i]){
                APPROACHING_BOUND = true;
            }

            // Initialize vectors for regression
            for (int j = 0; j < p_best.n_reps; j++){

                // Define a new value
                new_val = uniform(temp_ub, temp_lb);

                // Create a parameter set with the new value
                p_current = p_best;
                p_current.set_from_pair(var_name[i], new_val);

                // Save the new value (this takes advantage of rounding when pushed to parameter set
                X[j] = p_current.get_from_name(var_name[i]);

                // Run a team with that value
                Team T(p_current);
                T.new_start();
                T.solve();
                Y[j] = T.best_solution.back();
            }

            // Now, perform regression with Y and X
            quad_res = quad_max(X, Y);
            if(quad_res[3] > 0.03) {
                p_best.set_from_pair(var_name[i], quad_res[0]);
                var_vals[i] = p_best.get_from_name(var_name[i]);
                // Check to see if we're against a non-limiting edge solution
                if (quad_res[0] == vector_min(X) || quad_res[0] == vector_max(X)){
                    if (!APPROACHING_BOUND) {
                        EDGE_SOLUTION = true;
                    }
                }
            }

            if(verb) {
                cout << " = " << p_best.get_from_name(var_name[i])
                        << ", mean = " << quad_res[2]
                        << ", r2 = " << quad_res[3]
                        << ", " << (EDGE_SOLUTION ? "edge" : "interior") << endl;
            }

        }
        // Halve the step-sizes
        if(!EDGE_SOLUTION) {
            for (int i = 0; i < step_sizes.size(); i++) {
                step_sizes[i] /= 2.0;
            }
            if(verb){
                cout << "\t\t" << "All interior points. Updating step sizes." << endl;
            }
        }
        current_iteration++;
    }
}