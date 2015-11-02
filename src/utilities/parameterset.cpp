#include "../../include/utilities/parameterset.hpp"

//// Construct the thing
ParameterSet::ParameterSet(void){
    init_learn_path = "none";
}

//// Function to read variables from a file
void ParameterSet::set_from_file(std::string file_name) {

    std::ifstream inputFile(file_name);
    std::string line;
    std::string name;

    while (getline(inputFile, line))
    {
        std::istringstream ss(line);

        ss >> name;

        if(name == "NAGENTS")      ss >> n_agents;
        else if(name == "INTER")   ss >> interaction;
        else if(name == "TINIT")   ss >> initial_temperature;
        else if(name == "DELT")    ss >> delt;
        else if(name == "L_HIST")  ss >> history_length;
        else if(name == "NREPS")   ss >> n_reps;
        else if(name == "MAX_IT")  ss >> max_iter;
        else if(name == "S_BIAS")  ss >> s_bias;
        else if(name == "Q_BIAS")  ss >> q_bias;
        else if(name == "LEARN_CONST")  ss >> op_learn;
        else if(name == "LEARN_INIT")  ss >> init_learn_path;
        else if(name == "LEARN")  ss >> learning_style;
        else if(name == "SATFRAC") ss >> satisficing_fraction;
    }
}

//// Shows the current parameters
void ParameterSet::print_parameters(void) {
    std::cout << "Number of agents:  " <<  n_agents                        << std::endl;
    std::cout << "Interaction:       " <<  interaction                     << std::endl;
    std::cout << "Initial temp:      " <<  initial_temperature             << std::endl;
    std::cout << "Temp factor:       " <<  delt                            << std::endl;
    std::cout << "History length:    " <<  history_length                  << std::endl;
    std::cout << "Number of reps:    " <<  n_reps                          << std::endl;
    std::cout << "Max iterations:    " <<  max_iter                        << std::endl;
    std::cout << "Self-bias:         " <<  s_bias                          << std::endl;
    std::cout << "Quality-bias:      " <<  q_bias                          << std::endl;
    std::cout << "Learning style:    " <<  learning_style                  << std::endl;
    std::cout << "Initial knowledge: " <<  init_learn_path                 << std::endl;
    std::cout << "Operation learn:   " <<  op_learn                        << std::endl;
    std::cout << "Satisficing frac:  " <<  satisficing_fraction            << std::endl;
}

//// Sets parameters based on a vector
void ParameterSet::set_from_pair(std::string name, long double x) {
    if(name == "DELT")         delt = x;
    else if(name == "L_HIST")  history_length =static_cast <int> (std::round(x));
    else if(name == "NAGENTS") n_agents = static_cast <unsigned long> (std::round(x));
    else if(name == "TINIT")   initial_temperature = x;
    else if(name == "INTER")   interaction = x;
    else if(name == "S_BIAS")  s_bias = x;
    else if(name == "Q_BIAS")  q_bias = x;
    else if(name == "LEARN_CONST")  op_learn = x;
    else if(name == "SATFRAC") satisficing_fraction = x;
}

//// Get parameters from a string name
long double ParameterSet::get_from_name(std::string name) {
    if(name == "DELT")         return delt;
    else if(name == "L_HIST")  return history_length;
    else if(name == "NAGENTS") return n_agents;
    else if(name == "TINIT")   return initial_temperature;
    else if(name == "INTER")   return interaction;
    else if(name == "S_BIAS")  return s_bias;
    else if(name == "Q_BIAS")  return q_bias;
    else if(name == "LEARN_CONST")  return op_learn;
    else if(name == "SATFRAC") return satisficing_fraction;
    else                       return -1;
}

