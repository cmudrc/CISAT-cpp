#include "../../include/utils/parameters.hpp"

//// Construct the thing
Parameters::Parameters(void){}

//// Object function of the thing
long double Parameters::obj(vector<long double> x) {
    if(function == "griewank")       return griewank(x);
    else if(function == "ackley")    return ackley(x);
    else if(function == "rastigrin") return rastigrin(x);
    else                             return -1.0;
}

//// Function to read variables from a file
void Parameters::set_from_file(string file_name) {

    ifstream inputFile(file_name);
    string line;
    string name;

    while (getline(inputFile, line))
    {
        istringstream ss(line);

        ss >> name;

        if(name == "FUNC")         ss >> function;
        else if(name == "NAGENTS") ss >> n_agents;
        else if(name == "ADAPT")   ss >> adaptive;
        else if(name == "INTER")   ss >> interacting;
        else if(name == "TINIT")   ss >> temp_init;
        else if(name == "DELT")    ss >> delt;
        else if(name == "L_HIST")  ss >> history_length;
        else if(name == "NREPS")   ss >> n_reps;
        else if(name == "MAX_IT")  ss >> max_iter;
        else if(name == "DIMS")    ss >> D;
        else if(name == "UBND")    ss >> ub;
        else if(name == "LBND")    ss >> lb;

    }
}

//// Shows the current parameters
void Parameters::print_params(void) {
    cout << "Function:         " <<  function                        << endl;
    cout << "Number of agents: " <<  n_agents                        << endl;
    cout << "Adaptive?:        " <<  (adaptive ? "yes" : "no")       << endl;
    cout << "Interacting?:     " <<  (interacting ? "yes" : "no")    << endl;
    cout << "Initial temp:     " <<  temp_init                       << endl;
    cout << "Temp factor:      " <<  delt                            << endl;
    cout << "History length:   " <<  history_length                  << endl;
    cout << "Number of reps:   " <<  n_reps                          << endl;
    cout << "Max iterations:   " <<  max_iter                        << endl;
    cout << "Number of dims:   " <<  D                               << endl;
    cout << "Upper bound on x: " <<  ub                              << endl;
    cout << "Lower bound on x: " <<  lb                              << endl;
}

//// Sets parameters based on a vector
void Parameters::set_from_pair(string name, long double x) {
    if(name == "DELT")         delt = x;
    else if(name == "L_HIST")  history_length =static_cast <int> (round(x));
    else if(name == "NAGENTS") n_agents = static_cast <unsigned long> (round(x));
    else if(name == "TINIT")   temp_init = x;
}

//// Sets parameters based on a vector
long double Parameters::get_from_name(string name) {
    if(name == "DELT")         return delt;
    else if(name == "L_HIST")  return history_length;
    else if(name == "NAGENTS") return n_agents;
    else if(name == "TINIT")   return temp_init;
    else                       return -1;
}

