//    ┌─┬─────┐
//    ├─┼─────┤ CISAT Modeling Framework
//    │ │ McC │ Cognitively-Inspired Simulated Annealing Teams
//    └─┴─────┘

#include "./include/agents_and_teams/multiple_teams.hpp"
#include "./include/meta_optimization/univariate.hpp"
#include "./include/meta_optimization/pattern.hpp"
#include <sys/time.h>

// TODO: Add a status bar. 
// TODO: Clean up command line options so everything comes from a config.
// TODO Option to not save results to file
int main(int argc, char *argv[]) {

    // Random seed
    seed_time();

    // Start timing the code
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Variables to figure out what's going on
    long double delta;
    int max_iter = 10;
    bool bench = false;
    bool univariate = false;
    bool pattern = false;
    bool found_output = false;
    bool found_input = false;
    std::string input;
    std::string output;


    // Parse the inputs
    for(int i=1; i < argc; i++) {
        if      (std::string(argv[i]) == "--bench"    || std::string(argv[i]) == "-b") {
            bench = true;
        }
        else if (std::string(argv[i]) == "--univar"   || std::string(argv[i]) == "-u") {
            univariate = true;
            i++;
            max_iter = atoi(argv[i]);
        }
        else if (std::string(argv[i]) == "--pattern"  || std::string(argv[i]) == "-p") {
            pattern = true;
            i++;
            max_iter = atoi(argv[i]);
        }
        else if (std::string(argv[i]) == "--output"   || std::string(argv[i]) == "-o") {
            i++;
            output = std::string(argv[i]);
            found_output = true;
        }
        else if (std::string(argv[i]) == "--input"    || std::string(argv[i]) == "-i") {
            i++;
            input = std::string(argv[i]);
            found_input = true;
        }
        else if (std::string(argv[1]) == "--help"     || std::string(argv[i]) == "-h" || argc == 1) {
            std::cout << "You need help, bro" << std::endl;
            return 0;
        }
        else {
            std::cout << "cisat: Invalid option, '" << std::string(argv[i]) << "' is not recognized. Try running 'cisat --help' for help text." << std::endl;
            return 1;
        }
    }

    // Make sure there's an input file
    if(!found_input) {
        std::cout << "cisat: An input file was not provided, but is required for --bench, --univariate, and --pattern." << std::endl;
        return 1;
    }

    // Run benchmarking
    if(bench){
        // Initialize it
        MultipleTeams some_teams(input);

        // Print parameters
        some_teams.parameters.print_parameters();

        // Print output if requested
        std::cout << std::endl << some_teams.solve() << std::endl << std::endl;

        // Print cdf
        print(some_teams.cdf);

        // Save output if possible
        if(found_output){
            save_to_file(output, some_teams.best_solution);
        }
    }

    // Run stochastic univariate search
    if(univariate){
        // Make it
        UnivariateSearch US(input);

        // Print starting values
        US.best_parameters.print_parameters();

        // Solve it all
        US.solve(max_iter);

        // Output the final solution set to a file defined by argv2
        if(found_output) {
            US.save_settings(output);
        }

    }

    // Run pattern search
    if(pattern){
        // Make it
        PatternSearch PS(input);

        // If verbose, print beginning values
        PS.best_parameters.print_parameters();

        // Solve it all
        PS.solve(max_iter);

        // Output the final solution set to a file defined by argv2
        if(found_output) {
            PS.save_settings(output);
        }
    }

    // Take finished time and print duration
    gettimeofday(&end, NULL);
    delta = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

    std::cout.precision(2);
    std::cout << std::fixed << delta << " seconds elapsed." << std::endl;
    return 0;
}
