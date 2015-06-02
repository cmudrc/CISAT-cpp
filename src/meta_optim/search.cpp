#include "../../include/meta_optim/pattern.hpp"

// Null initializer for search
Search::Search(){}

void Search::parse_param_file(string file_name){
    // Set the parameters to their current values in the setup file
    p_best.set_from_file(file_name);

    // Step through the setup file and build parameter lists
    ifstream inputFile(file_name);
    string line;
    string name;
    long double lower_limit;
    long double upper_limit;
    long double temp;
    bool indicator;

    while (getline(inputFile, line))
    {
        // Read a line
        istringstream ss(line);
        ss >> name >> temp >> indicator;

        if(indicator) {
            ss >> lower_limit;
            lower_lims.push_back(lower_limit);
            ss >> upper_limit;
            upper_lims.push_back(upper_limit);
            var_name.push_back(name);
            var_vals.push_back(temp);
            step_sizes.push_back(0.25*temp);
        }
    }
}


void Search::save_settings(string file_name){
    // Open a file stream
    ofstream myfile;

    // Open a file on that file stream
    myfile.open(file_name);

    // Print a file with appropriate data
    myfile << "FUNC    " << p_best.function << endl;
    myfile << "NAGENTS " << p_best.n_agents << endl;
    myfile << "ADAPT   " << p_best.adaptive << endl;
    myfile << "INTER   " << p_best.interacting << endl;
    myfile << "TINIT   " << p_best.temp_init << endl;
    myfile << "DELT    " << p_best.delt << endl;
    myfile << "L_HIST  " << p_best.history_length << endl;
    myfile << "NREPS   " << p_best.n_reps << endl;
    myfile << "MAX_IT  " << p_best.max_iter << endl;
    myfile << "DIMS    " << p_best.D << endl;
    myfile << "UBND    " << p_best.ub << endl;
    myfile << "LBND    " << p_best.lb << endl;

    myfile.close();
}
