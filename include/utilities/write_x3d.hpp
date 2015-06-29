#ifndef UTILITIES__WRITE_VRML_HPP
#define UTILITIES__WRITE_VRML_HPP

#include <fstream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// TODO: Write a class prototype to add components to a vrml file
class WriteX3D {
public:

    // Constructors
    WriteX3D(void);
    void open_file(std::string file_path);
    void close_file(void);
    void write_sphere(long double x, long double y, long double z, long double radius);
    void write_line(long double x1, long double y1, long double z1, long double x2, long double y2, long double z2);

private:
    std::ofstream my_file;

};


#endif