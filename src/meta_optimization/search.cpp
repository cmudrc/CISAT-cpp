#include "../../include/meta_optimization/pattern.hpp"

// Null initializer for search
Search::Search(){}

void Search::parse_parameter_file(std::string file_name){
    // Set the parameters to their current values in the setup file
    best_parameters.set_from_file(file_name);

    // Step through the setup file and build parameter lists
    std::ifstream inputFile(file_name);
    std::string line;
    std::string name;
    long double lower_limit;
    long double upper_limit;
    long double temp;
    bool to_be_used_for_optimization;

    while (getline(inputFile, line))
    {
        // Read a line
        std::istringstream ss(line);
        ss >> name >> temp >> to_be_used_for_optimization;

        if(to_be_used_for_optimization) {
            ss >> lower_limit;
            lower_limits.push_back(lower_limit);
            ss >> upper_limit;
            upper_limits.push_back(upper_limit);
            variable_names.push_back(name);
            variable_values.push_back(temp);
            step_sizes.push_back(0.25*temp);
        }
    }
}


void Search::save_settings(std::string file_name){
    // Open a file stream
    std::ofstream myfile;

    // Open a file on that file stream
    myfile.open(file_name);

    // Print a file with appropriate data
    myfile << "NAGENTS " << best_parameters.n_agents << std::endl;
    myfile << "INTER   " << best_parameters.interaction << std::endl;
    myfile << "TINIT   " << best_parameters.initial_temperature << std::endl;
    myfile << "DELT    " << best_parameters.delt << std::endl;
    myfile << "L_HIST  " << best_parameters.history_length << std::endl;
    myfile << "NREPS   " << best_parameters.n_reps << std::endl;
    myfile << "MAX_IT  " << best_parameters.max_iter << std::endl;
    myfile << "S_BIAS  " << best_parameters.s_bias << std::endl;
    myfile << "Q_BIAS  " << best_parameters.q_bias << std::endl;
    myfile << "OLEARN  " << best_parameters.op_learn << std::endl;
    myfile << "SATFRAC " << best_parameters.satisficing_fraction << std::endl;

    myfile.close();
}
