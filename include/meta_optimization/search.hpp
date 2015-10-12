//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  include
//  └─┴─────┘  ││   └─meta_optimization
//             ││      └─search.hpp

#ifndef META_OPTIMIZATION__SEARCH_HPP
#define META_OPTIMIZATION__SEARCH_HPP

class Search {
public:
    void parse_parameter_file(std::string file_name);
    void save_settings(std::string file_name);

    //// Variables
    ParameterSet best_parameters;       // The parameters of the simulation
    std::vector<std::string> variable_names;
    std::vector<long double> variable_values;
    std::vector<long double> lower_limits;
    std::vector<long double> upper_limits;
    std::vector<long double> step_sizes;
};

#endif