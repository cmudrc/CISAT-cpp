#include "../../include/utilities/write_x3d.hpp"

// TODO: Write functions to add components to a vrml file
void WriteX3D::open_file(std::string file_name) {
    // Open a file on that file stream
    my_file.open(file_name);
}

void WriteX3D::close_file(void) {
    my_file.close();
}