#include "../../include/utils/customprint.hpp"

//// Function to print an int
void print(int x){
    cout<<x<<endl;
}

//// Function to print a long double
void print(long double x){
    cout<<x<<endl;
}

//// Function to print the size of a vector
void print(vector<long double>::size_type x){
    cout<<x<<endl;
}

//// Function to print a vector. Black magic.
void print(vector<long double> x){
    int end = static_cast <int> (x.size()-1);
    cout<<scientific<<"[ ";
    for(int i=0; i<x.size(); i++){
        if(i!=end) {
            cout << x[i] << ", ";
            if ((i + 1) % 10 == 0) {
                cout << endl << "  ";
            }
        } else {
            cout << x[i] << " ]" << endl;
        }
    }
}



//// Save a vector to a file
void save_to_file(string file_path, vector<long double> x){
    // Open a file stream
    ofstream my_file;

    // Open a file on that file stream
    my_file.open(file_path);

    // Set scientific notation. Mostly for nice alignment
    my_file << scientific;

    // Step through the vector, and print an element on each line
    for(int i=0; i<x.size(); i++){
        my_file << x[i]  << endl;
    }

    // Close the file
    my_file.close();
}


//// Save a vector of vectors to file. This happens a lot, actually.
void save_to_file(string file_path, vector< vector<long double> > x){
    // Open a file stream
    ofstream my_file;

    // Open a file on that file stream
    my_file.open(file_path);

    // Set to scientific notation, mostly for alignment
    my_file << scientific;

    // Print each sub-vector to a column.
    for(int i=0; i<x[0].size(); i++) {
        for(int j=0; j<x.size(); j++){
            my_file << x[j][i] << "\t";
        }
        my_file << endl;
    }

    // Close the file
    my_file.close();
}
