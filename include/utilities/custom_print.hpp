#ifndef UTILITIES__CUSTOM_PRINT_HPP
#define UTILITIES__CUSTOM_PRINT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// Functions to print variables
void print(int x);
void print(long double x);
void print(std::vector<long double>);
void print(std::vector<long double>::size_type x);

// Write to file
void save_to_file(std::string file_path, std::vector<long double>);
void save_to_file(std::string file_path, std::vector< std::vector<long double> >);
void save_to_file(std::string file_path, std::vector< std::vector< std::vector<long double> > > x);

#endif