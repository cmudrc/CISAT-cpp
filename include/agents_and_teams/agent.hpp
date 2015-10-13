//  ┌─┬─────┐  ││  CISAT: The Cognitively-Inspired Simulated
//  ├─┼─────┤  ││         Annealing Teams Modeling Framework
//  │ │ McC │  ││  include
//  └─┴─────┘  ││   └─agents_and_teams
//             ││      └─agent.hpp

#ifndef AGENTS_AND_TEAMS__AGENT_HPP
#define AGENTS_AND_TEAMS__AGENT_HPP

#include <list>
#include "../utilities/parameterset.hpp"
#include "../utilities/make_random.hpp"
#include "../utilities/stats.hpp"
#include "../utilities/custom_print.hpp"
#include "../problem_statements/fluid_network.hpp"

class Agent {
public:
    // A function to initialize the agent with a specific ID
    Agent(int ID, ParameterSet p);

    // A function that selects a random starting point, and pushes it to other agents.
    void new_start(void);

    // A function to perform an iteration of SA.
    void iterate(int iter);

    //// Variables
    ParameterSet parameters;             // A parameters structure that holds much of the SA info
    int agent_id;                   // Agent ID, tells it where to store info in static vectors.
    int iteration_number;     // The number of the current iteration
    int last_operation;       // The last operation performed by the agent
    long double temperature;  // The current temperature
    long double triki_temperature;
    long double current_solution_quality;        // The function value of the current solution
    long double best_solution_so_far;
    std::vector<long double> objective_weighting;
    Solution current_solution; // The value of the current solution
    std::vector< std::vector<long double> > move_oper_pref; // preference for different move operators
    std::deque<long double> history;   // History of quality

    //// Accessible everywhere
    static std::vector<Solution> all_current_solutions;
    static std::vector< std::vector<long double> > all_current_objective_weightings;

private:
    //// Functions
    Solution candidate_solution(void);
    void update_temp(void);                  // Updates the temperature.
    long double update_triki(void);

};

#endif