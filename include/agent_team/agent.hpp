#ifndef AGENT_HPP
#define AGENT_HPP

#include <list>
#include "../utils/parameters.hpp"
#include "../utils/makerandom.hpp"
#include "../utils/stats.hpp"
#include "../utils/customprint.hpp"
#include "../problem_statements/ackley.hpp"

#define NUMBER_OF_MOVE_OPERATORS 60;

using namespace std;

class Agent {
public:
    //// Functions
    Agent(int ID, Parameters p);          // A function to initialize the agent with a specific ID
    Agent(void);            // A function to intialize an agent inline for the purpose of modifying static vectors.
    void new_start(void);   // A function that selects a random starting point, and pushes it to other agents.
    void iterate(int iter); // A function to perform an iteration of SA.

    //// Variables
    Parameters p;             // A parameters structure that holds much of the SA info
    int id;                   // Agent ID, tells it where to store info in static vectors.
    int iteration_number;     // The number of the current iteration
    long double Ti;                // The current temperature
    long double fx_current;        // The function value of the current solution
    Solution x_current; // The value of the current solution
    deque<long double> history;   // History of quality

    //// Accessible everywhere
    static vector<long double> all_fx_current;         // Function value of all agents current solutions
    static vector<Solution> all_xx_current;

private:
    //// Functions
    Solution candidate_solution(void);
    void update_temp(void);                  // Updates the temperature.
    long double update_triki(void);
    long double update_cauchy(void);
};

#endif