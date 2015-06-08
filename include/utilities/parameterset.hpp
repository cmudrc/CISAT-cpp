#ifndef UTILITIES__PARAMETERS_HPP
#define UTILITIES__PARAMETERS_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>

class ParameterSet {
public:
    //// Variables
    // Number of times to repeat the solution
    unsigned long n_reps;
    // Maximum number of iterations to perform
    unsigned long max_iter;
    // Float storing interaction
    long double interaction;
    int history_length;
    unsigned long n_agents;
    long double initial_temperature;
    long double delt;
    long double s_bias;
    long double q_bias;
    long double op_learn;
    long double satisficing_fraction;

    //// Functions
    ParameterSet(void);
    void set_from_file(std::string file_name);
    void set_from_pair(std::string name, long double x);
    void print_params(void);
    long double get_from_name(std::string name);

private:
    //nothing yet
};

#endif