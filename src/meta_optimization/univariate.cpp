#include "../../include/meta_optimization/univariate.hpp"

UnivariateSearch::UnivariateSearch(std::string file_name){
    seed_time();
    parse_parameter_file(file_name);
}

void UnivariateSearch::solve(int max_iter, bool verb){
    // Stores the current iteration and values
    current_iteration = 0;
    ParameterSet p_current;

    // Stores a new value
    long double new_val = 0;

    // Keeps track of whether or not an edge solution has been found
    bool EDGE_SOLUTION;

    // Keeps track of whether a bound is being approached
    bool APPROACHING_BOUND;

    // Stores values to feed to quadratic regression
    std::vector<long double> X(p_best.n_reps, 0.0);
    std::vector<long double> Y(p_best.n_reps, 0.0);

    // Stores the results from the quadratic regression
    std::vector<long double> quad_res;
    long double temp_ub;
    long double temp_lb;
    if(verb) {
        std::cout << "\nBeginning Optimization Routine" << std::endl;
    }

    // Do some iterations, bro. Get mad optimized.
    while(current_iteration < max_iter) {
        if(verb) {
            std::cout << "\tIteration " << current_iteration + 1 << " of " << max_iter << std::endl;
        }
        EDGE_SOLUTION = false;
        APPROACHING_BOUND = false;
        // Within each iteration, step in each direction
        for (int i = 0; i < variable_names.size(); i++) {
            if(verb) {
                std::cout << "\t\tComputing " << variable_names[i];
            }

            // Draw a random variable in the param range
            temp_ub = std::min(variable_values[i]+step_sizes[i], upper_limits[i]);
            temp_lb = std::max(variable_values[i]-step_sizes[i], lower_limits[i]);

            // Check to see if we're up against a bound
            if(temp_ub == upper_limits[i] || temp_lb == lower_limits[i]){
                APPROACHING_BOUND = true;
            }

            // Initialize vectors for regression
            for (int j = 0; j < p_best.n_reps; j++){

                // Define a new value
                new_val = uniform(temp_ub, temp_lb);

                // Create a parameter set with the new value
                p_current = p_best;
                p_current.set_from_pair(variable_names[i], new_val);

                // Save the new value (this takes advantage of rounding when pushed to parameter set
                X[j] = p_current.get_from_name(variable_names[i]);

                // Run a team with that value
                Team T(p_current);
                T.new_start();
                T.solve();
                Y[j] = T.best_solution.back()[0];
            }

            // Now, perform regression with Y and X
            quad_res = quad_max(X, Y);
            if(quad_res[3] > 0.03) {
                p_best.set_from_pair(variable_names[i], quad_res[0]);
                variable_values[i] = p_best.get_from_name(variable_names[i]);
                // Check to see if we're against a non-limiting edge solution
                if (quad_res[0] == vector_min(X) || quad_res[0] == vector_max(X)){
                    if (!APPROACHING_BOUND) {
                        EDGE_SOLUTION = true;
                    }
                }
            }

            if(verb) {
                std::cout << " = " << p_best.get_from_name(variable_names[i])
                        << ", mean = " << quad_res[2]
                        << ", r2 = " << quad_res[3]
                        << ", " << (EDGE_SOLUTION ? "edge" : "interior") << std::endl;
            }

        }
        // Halve the step-sizes
        if(!EDGE_SOLUTION) {
            for (int i = 0; i < step_sizes.size(); i++) {
                step_sizes[i] /= 2.0;
            }
            if(verb){
                std::cout << "\t\t" << "All interior points. Updating step sizes." << std::endl;
            }
        }
        current_iteration++;
    }
}