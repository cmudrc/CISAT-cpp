#ifndef UTILITIES__CUSTOM_PRINT_HPP
#define UTILITIES__CUSTOM_PRINT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// Template for printing a single thing
template <typename Type>
void print(Type x) {
    std::cout << x << std::endl;
}

// Template for printing multiple things in a vector
template <typename Type>
void print(std::vector<Type> x){
    int end = static_cast <int> (x.size()-1);
    std::cout<<std::scientific<<"[ ";
    for(int i=0; i<x.size(); i++){
        if(i!=end) {
            std::cout << x[i] << ", ";
            if ((i + 1) % 10 == 0) {
                std::cout << std::endl << "  ";
            }
        } else {
            std::cout << x[i] << " ]" << std::endl;
        }
    }
}

// Template for printing SO MANY things in a vector of vectors
template <typename Type>
void print(std::vector< std::vector<Type> >x){
    int end = static_cast <int> (x.size()-1);

    std::cout<<std::scientific<<"[ ";
    for(int i=0; i<x.size(); i++){
        if(i!=end) {
            std::cout << x[i] << ", ";
            if ((i + 1) % 10 == 0) {
                std::cout << std::endl << "  ";
            }
        } else {
            std::cout << x[i] << " ]" << std::endl;
        }
    }
}



// Write to file
void save_to_file(std::string file_path, std::vector<long double>);
void save_to_file(std::string file_path, std::vector< std::vector<long double> >);
void save_to_file(std::string file_path, std::vector< std::vector< std::vector<long double> > > x);

#endif