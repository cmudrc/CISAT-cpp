#include "../../include/meta_optimization/univariate.hpp"

UnivariateSearch::UnivariateSearch(std::string file_name){
    seed_time();
    parse_parameter_file(file_name);
}

void UnivariateSearch::solve(int max_iter, bool verb){
    // Stores the current iteration and values
    current_iteration = 0;
    ParameterSet current_parameters;

    // Stores a new value
    long double new_value = 0;

    // Keeps track of whether or not an edge solution has been found
    bool is_edge_solution;

    // Keeps track of whether a bound is being approached
    bool is_at_bound;

    // Stores values to feed to quadratic regression
    std::vector<long double> X(best_parameters.n_reps, 0.0);
    std::vector<long double> Y(best_parameters.n_reps, 0.0);

    // Stores the results from the quadratic regression
    std::vector<long double> regression_results;
    long double safe_upper_bound;
    long double safe_lower_bound;
    if(verb) {
        std::cout << "\nBeginning Optimization Routine" << std::endl;
    }

    // Do some iterations, bro. Get mad optimized.
    while(current_iteration < max_iter) {
        if(verb) {
            std::cout << "\tIteration " << current_iteration + 1 << " of " << max_iter << std::endl;
        }
        is_edge_solution = false;
        is_at_bound = false;
        // Within each iteration, step in each direction
        for (int i = 0; i < variable_names.size(); i++) {
            if(verb) {
                std::cout << "\t\tComputing " << variable_names[i];
            }

            // Draw a random variable in the param range
            safe_upper_bound = std::min(variable_values[i]+step_sizes[i], upper_limits[i]);
            safe_lower_bound = std::max(variable_values[i]-step_sizes[i], lower_limits[i]);

            // Check to see if we're up against a bound
            if(safe_upper_bound == upper_limits[i] || safe_lower_bound == lower_limits[i]){
                is_at_bound = true;
            }

            // Initialize vectors for regression
            for (int j = 0; j < best_parameters.n_reps; j++){

                // Define a new value
                new_value = uniform(safe_upper_bound, safe_lower_bound);

                // Create a parameter set with the new value
                current_parameters = best_parameters;
                current_parameters.set_from_pair(variable_names[i], new_value);

                // Save the new value (this takes advantage of rounding when pushed to parameter set
                X[j] = current_parameters.get_from_name(variable_names[i]);

                // Run a team with that value
                Team T(current_parameters);
                T.new_start();
                T.solve();
                Y[j] = T.best_solution.back();
            }

            // Now, perform regression with Y and X
            regression_results = quad_max(X, Y);
            if(regression_results[3] > 0.03) {
                best_parameters.set_from_pair(variable_names[i], regression_results[0]);
                variable_values[i] = best_parameters.get_from_name(variable_names[i]);
                // Check to see if we're against a non-limiting edge solution
                if (regression_results[0] == vector_minimum(X) || regression_results[0] == vector_maximum(X)){
                    if (!is_at_bound) {
                        is_edge_solution = true;
                    }
                }
            }

            if(verb) {
                std::cout << " = " << best_parameters.get_from_name(variable_names[i])
                        << ", mean = " << regression_results[2]
                        << ", r2 = " << regression_results[3]
                        << ", " << (is_edge_solution ? "edge" : "interior") << std::endl;
            }

        }
        // Halve the step-sizes
        if(!is_edge_solution) {
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