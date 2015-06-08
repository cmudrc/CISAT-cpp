#include "../../include/utilities/custom_print.hpp"

//// Function to print an int
void print(int x){
    std::cout<<x<<std::endl;
}

//// Function to print a long double
void print(long double x){
    std::cout<<x<<std::endl;
}

//// Function to print the size of a vector
void print(std::vector<long double>::size_type x){
    std::cout<<x<<std::endl;
}

//// Function to print a vector. Black magic.
void print(std::vector<long double> x){
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



//// Save a vector to a file
void save_to_file(std::string file_path, std::vector<long double> x){
    // Open a file stream
    std::ofstream my_file;

    // Open a file on that file stream
    my_file.open(file_path);

    // Set scientific notation. Mostly for nice alignment
    my_file << std::scientific;

    // Step through the vector, and print an element on each line
    for(int i=0; i<x.size(); i++){
        my_file << x[i]  << std::endl;
    }

    // Close the file
    my_file.close();
}


//// Save a vector of vectors to file. This happens a lot, actually.
void save_to_file(std::string file_path, std::vector< std::vector<long double> > x){
    // Open a file stream
    std::ofstream my_file;

    // Open a file on that file stream
    my_file.open(file_path);

    // Set to scientific notation, mostly for alignment
    my_file << std::scientific;

    // Print each sub-vector to a column.
    for(int i=0; i<x[0].size(); i++) {
        for(int j=0; j<x.size(); j++){
            my_file << x[j][i] << "\t";
        }
        my_file << std::endl;
    }

    // Close the file
    my_file.close();
}
