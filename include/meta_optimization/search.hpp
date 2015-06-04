#ifndef META_OPTIMIZATION__SEARCH_HPP
#define META_OPTIMIZATION__SEARCH_HPP

using namespace std;

class Search {
public:
    Search();
    void parse_param_file(string file_name);
    void save_settings(string file_name);

    //// Variables
    Parameters p_best;       // The parameters of the simulation
    vector<string> var_name;
    vector<long double> var_vals;
    vector<long double> lower_lims;
    vector<long double> upper_lims;
    vector<long double> step_sizes;
};

#endif