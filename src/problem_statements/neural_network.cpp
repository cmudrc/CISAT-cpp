//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─neural_network.cpp

#if PROBLEM_STATEMENT == NEURAL
#include "../../include/problem_statements/neural_network.hpp"

// Graph grammar characteristics
const  unsigned long  Solution::number_of_move_ops   = 7;
const  unsigned long  Solution::number_of_objectives = 1;
const  std::string    Solution::name                 = "Gravity Fed Fluid Network";
const  long double    Solution::goal                 = 0.0;

std::vector< std::map<std::string, long double> > Solution::seed_graph_parameters = {};


// Null constructor
// TODO: See if this is really needed
Solution::Solution(void){}


Solution::Solution(bool){
    // Give the solution a unique ID and increment the counter
    solution_id = solution_counter;
    solution_counter++;

    // Create seed graph
    create_seed_graph();

    // Initialize quality
    quality.assign(number_of_objectives, LDBL_MAX);
    compute_quality();
}


//
void Solution::apply_move_operator(int move_type){

}


//
void Solution::save_as_x3d(std::string save_to_file){

}

// Functions
void Solution::compute_quality(void){

}


void Solution::create_seed_graph(void){

}

// Move operators for Campbell


bool Solution::is_valid(void){

}


#endif