#ifndef UTILITIES__PARAMETERS_HPP
#define UTILITIES__PARAMETERS_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


class Parameters{
public:
    //// Variables
    // Must be set separately
    unsigned long n_reps;
    unsigned long max_iter;

    bool adaptive;
    bool interacting;
    int history_length;
    unsigned long n_agents;
    long double temp_init;
    long double delt;
    long double s_bias;
    long double q_bias;
    long double op_learn;

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