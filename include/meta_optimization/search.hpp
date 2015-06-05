#ifndef META_OPTIMIZATION__SEARCH_HPP
#define META_OPTIMIZATION__SEARCH_HPP

using namespace std;

class Search {
public:
    Search();
    void parse_parameter_file(string file_name);
    void save_settings(string file_name);

    //// Variables
    Parameters p_best;       // The parameters of the simulation
    vector<string> variable_names;
    vector<long double> variable_values;
    vector<long double> lower_limits;
    vector<long double> upper_limits;
    vector<long double> step_sizes;
};

#endif