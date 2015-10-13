//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─structure.cpp

#include "../../include/problem_statements/structure.hpp"

// Graph grammar characteristics
const  unsigned long  Solution::number_of_move_ops   = 7;
const  unsigned long  Solution::number_of_objectives = 1;
const  std::string    Solution::name                 = "Gravity Fed Fluid Network";
const  long double    Solution::goal                 = 0.0;

// Material constants
const  long double    Solution::E               = 209*std::pow(10,9); // Pa
const  long double    Solution::Fy              = 250*std::pow(10,6); // Pa

// Problem definition
std::vector< std::map<std::string, long double> > Solution::seed_graph_parameters = {
        {
                {"x", 0.00}, // [m]
                {"y", 10.00}, // [m]
                {"z", 0.00}, // [m]
                {"F", 35000.00}, // [N]
                {"rx", 0}, // [bool]
                {"ry", 0}, // [bool]
                {"rz", 1} // [bool]
        }, {
                {"x", 1.00}, // [m]
                {"y", 10.00}, // [m]
                {"z", 0.00}, // [m]
                {"F", 0.00}, // [N]
                {"rx", 1}, // [bool]
                {"ry", 1}, // [bool]
                {"rz", 1} // [bool]
        }, {
                {"x", -1.00}, // [m]
                {"y", 0.00}, // [m]
                {"z", 0.00}, // [m]
                {"F", 0.00}, // [N]
                {"rx", 1}, // [bool]
                {"ry", 1}, // [bool]
                {"rz", 1} // [bool]
        }
};

// Integer to assign unique IDs to solutions
int Solution::solution_counter = 0;


// Null constructor
Solution::Solution(void) {}


// A real constructor
Solution::Solution(bool) {
    // Give the solution a unique ID and increment the counter
    solution_id = solution_counter;
    solution_counter++;

    // Create seed graph
    create_seed_graph();

    // Initialize quality
    quality.assign(number_of_objectives, LDBL_MAX);
    compute_quality();
}

