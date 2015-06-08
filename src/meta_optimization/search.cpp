#include "../../include/meta_optimization/pattern.hpp"

// Null initializer for search
Search::Search(){}

void Search::parse_parameter_file(std::string file_name){
    // Set the parameters to their current values in the setup file
    p_best.set_from_file(file_name);

    // Step through the setup file and build parameter lists
    std::ifstream inputFile(file_name);
    std::string line;
    std::string name;
    long double lower_limit;
    long double upper_limit;
    long double temp;
    bool INDICATOR;

    while (getline(inputFile, line))
    {
        // Read a line
        std::istringstream ss(line);
        ss >> name >> temp >> INDICATOR;

        if(INDICATOR) {
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
    myfile << "NAGENTS " << p_best.n_agents << std::endl;
    myfile << "INTER   " << p_best.interaction << std::endl;
    myfile << "TINIT   " << p_best.initial_temperature << std::endl;
    myfile << "DELT    " << p_best.delt << std::endl;
    myfile << "L_HIST  " << p_best.history_length << std::endl;
    myfile << "NREPS   " << p_best.n_reps << std::endl;
    myfile << "MAX_IT  " << p_best.max_iter << std::endl;
    myfile << "S_BIAS  " << p_best.s_bias << std::endl;
    myfile << "Q_BIAS  " << p_best.q_bias << std::endl;
    myfile << "OLEARN  " << p_best.op_learn << std::endl;
    myfile << "SATFRAC " << p_best.satisficing_fraction << std::endl;

    myfile.close();
}
