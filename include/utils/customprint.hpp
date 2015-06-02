#ifndef CUSTOMPRINT_HPP
#define CUSTOMPRINT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Functions to print variables
void print(int x);
void print(long double x);
void print(vector<long double>);
void print(vector<long double>::size_type x);

// Write to file
void save_to_file(string file_path, vector<long double>);
void save_to_file(string file_path, vector< vector<long double> >);

#endif