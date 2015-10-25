//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  src
//  └─┴─────┘  ││   └─problem_statements
//             ││      └─neural_network.cpp

#if PROBLEM_STATEMENT == NEURAL
#include "../../include/problem_statements/neural_network.hpp"

// Graph grammar characteristics
const  unsigned long  Solution::number_of_move_ops   = 6;
const  unsigned long  Solution::number_of_objectives = 1;
const  long double    Solution::goal                 = 0.0;

std::vector< std::map<std::string, long double> > Solution::seed_graph_parameters = {};


// Null constructor
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


#if RULE_SET == CAMPBELL
void Solution::apply_move_operator(int rule_number){
    switch(rule_number) {
        case 0:
            r1_connect_with_edge();
            break;
        case 1:
            r2_connect_with_noded_edge();
            break;
        case 2:
            r3_replace_with_noded_edge();
            break;
        case 3:
            r4_add_bypass();
            break;
        case 4:
            r5_add_parallel_edge();
            break;
        case 5:
            r6_add_hidden_node();
            break;
        default:
            break;
    }

    // Compute the quality
    compute_quality();

    // Increment solution counters and things?
    solution_counter++;
    solution_id++;
}
#endif

//
void Solution::save_as_x3d(std::string save_to_file){

}

// Functions
void Solution::compute_quality(void){

}


void Solution::create_seed_graph(void){

}

// Move operators for Campbell
void Solution::r1_connect_with_edge(void){
    //TODO: Write function for Rule #1
}


// This function...
void Solution::r2_connect_with_noded_edge(void){
    //TODO: Write function for Rule #2
}


// This function...
void Solution::r3_replace_with_noded_edge(void){
    //TODO: Write function for Rule #3
}


// This function...
void Solution::r4_add_bypass(void){
    //TODO: Write function for Rule #4
}


// This function...
void Solution::r5_add_parallel_edge(void){
    //TODO: Write function for Rule #5
}


// This function...
void Solution::r6_add_hidden_node(void){
    //TODO: Write function for Rule #6
}



bool Solution::is_valid(void){
    return true;
}


#endif