#include "../../include/utilities/write_vrml.hpp"

// TODO: Write functions to add components to a vrml file
void WriteVRML::open_file(std::string file_name) {
    // Open a file stream
    std::ofstream my_file;

    // Open a file on that file stream
    my_file.open(file_name);
}


void WriteVRML::close_file(void) {
    my_file.close();
}