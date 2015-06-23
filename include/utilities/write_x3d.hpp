#ifndef UTILITIES__WRITE_VRML_HPP
#define UTILITIES__WRITE_VRML_HPP

#include <fstream>
#include <ostream>
#include <iostream>
#include <string>

// TODO: Write a class prototype to add components to a vrml file
class WriteX3D {
public:

    // Constructors
    WriteX3D(void);
    WriteX3D(std::string file_path);
    void open_file(std::string file_path);
    void close_file(void);

private:
    std::ofstream my_file;

};


#endif