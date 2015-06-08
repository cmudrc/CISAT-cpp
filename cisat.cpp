#include "./include/agents_and_teams/multiple_teams.hpp"
#include "./include/meta_optimization/univariate.hpp"
#include "./include/meta_optimization/pattern.hpp"
#include <sys/time.h>

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
    bool verb = false;
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
        else if (std::string(argv[i]) == "--verbose"  || std::string(argv[i]) == "-v") {
            verb = true;
        }
        else if (std::string(argv[1]) == "--help"     || std::string(argv[i]) == "-h" || argc == 1) {
            std::cout << "You need help, bro" << std::endl;
            return 0;
        }
        else {
            std::cout << "hsat: Invalid option, '" << std::string(argv[i]) << "' is not recognized. Try running 'hsat --help' for help text." << std::endl;
            return 1;
        }
    }

    // Make sure there's an input file
    if(!found_input) {
        std::cout << "hsat: An input file was not provided, but is required for --bench, --univariate, and --pattern." << std::endl;
        return 1;
    }

    // Run benchmarking
    if(bench){
        // Initialize it
        MultipleTeams MT(input);

        // Print parameters if verbose
        if(verb){
            Solution::print_surface_characteristics();
            MT.p.print_params();
        }

        // Print output if requested
        MT.solve();
        std::cout << std::endl << "Output saved." << std::endl << std::endl;

        // Save output if possible
        if(found_output){
            save_to_file(output, MT.best_solution);
        }
    }

    // Run stochastic univariate search
    if(univariate){
        // Make it
        UnivariateSearch US(input);

        // If verbose, print beginning values
        if(verb){
            US.p_best.print_params();
        }

        // Solve it all
        US.solve(max_iter, verb);

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
        if(verb){
            PS.p_best.print_params();
        }

        // Solve it all
        PS.solve(max_iter, verb);

        // Output the final solution set to a file defined by argv2
        if(found_output) {
            PS.save_settings(output);
        }
    }

    // Take finished time and print duration
    gettimeofday(&end, NULL);
    delta = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

    std::cout.precision(2);
    if(verb) {
        std::cout << std::fixed << delta << " seconds elapsed." << std::endl;
    }
    return 0;
}
