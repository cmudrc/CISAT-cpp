#include "../../include/problem_statements/fluid_channels.hpp"

// Integer to assign unique IDs to solutions
int Solution::solution_counter = 0;
const int Solution::number_of_move_ops = 2;
const int Solution::number_of_objectives = 3;
const std::string Solution::name = "Fluid Problem";
const long double Solution::goal = 0.1;
const long double Solution::upper_bound = 10;
const long double Solution::lower_bound = -10;

Solution::Solution(void) {
    // Give the solution a unique ID and increment the counter
    solution_id = solution_counter;
    solution_counter++;

    //
}

void Solution::compute_quality() {
}

void Solution::apply_move_operator(int n, long double size) {
}

void Solution::print_surface_characteristics() {
    std::cout << "Problem Characteristics" << std::endl;
    std::cout << "\tName: " << name << std::endl;
    std::cout << "\tGoal: " << goal << std::endl;
    std::cout << "\tNumber of move operators: " << number_of_move_ops << std::endl;
}
