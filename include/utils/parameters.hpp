#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "objective.hpp"

using namespace std;


class Parameters{
public:
    //// Variables
    // Must be set separately
    unsigned long n_reps;
    unsigned long max_iter;
    long double ub;
    long double lb;
    string function;

    bool adaptive;
    bool interacting;
    int history_length;
    unsigned long n_agents;
    long double temp_init;
    long double delt;

    //// Functions
    Parameters(void);
    void set_from_file(string file_name);
    void set_from_pair(string name, long double x);
    void print_params(void);
    long double get_from_name(string name);

private:
    //nothing yet
};

#endif