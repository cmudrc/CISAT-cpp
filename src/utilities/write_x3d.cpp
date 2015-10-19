#include "../../include/utilities/write_x3d.hpp"

WriteX3D::WriteX3D(void) {}

void WriteX3D::open_file(std::string file_name, long double x, long double y, long double z) {
    // Open a file on that file stream
    my_file.open(file_name);

    // Write the boiler plate
    my_file << "<!DOCTYPE html >" << std::endl;
    my_file << "<html>" << std::endl;
    my_file << "    <head>" << std::endl;
    my_file << "        <meta http-equiv=\"X-UA-Compatible\" content=\"chrome=1\" />" << std::endl;
    my_file << "        <meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\" />" << std::endl;
    my_file << "        <title>Hello World</title>" << std::endl;
    my_file << "        <link rel=\"stylesheet\" type=\"text/css\" href=\"./x3dom.css\" />" << std::endl;
    my_file << "        <script type=\"text/javascript\" src=\"./x3dom.js\"></script>" << std::endl;
    my_file << "    </head>" << std::endl;
    my_file << "    <body>" << std::endl;
    my_file << "        <x3d xmlns=\"http://www.x3dom.org/x3dom\" showStat=\"false\" showLog=\"false\" x=\"0px\" y=\"0px\" style='width: 100%; height: 100%;'> " << std::endl;
    my_file << "            <scene>" << std::endl;
    my_file << "                <viewpoint position='" << x << " " << y << " " << z << "' ></viewpoint>" << std::endl;
}

void WriteX3D::write_sphere(long double x, long double y, long double z, long double radius) {
    my_file << "                <Transform translation=\"" << x << " " << y << " " <<  z << "\">" << std::endl;
    my_file << "                    <Shape>" << std::endl;
    my_file << "                        <Appearance>" << std::endl;
    my_file << "                            <Material diffuseColor='0.5 0.5 0.5' transparency=\"0\"></Material>" << std::endl;
    my_file << "                        </Appearance>" << std::endl;
    my_file << "                        <sphere radius=\"" << radius << "\"></sphere>" << std::endl;
    my_file << "                    </Shape>" << std::endl;
    my_file << "                </Transform>" << std::endl;
}

void WriteX3D::write_line(long double x1, long double y1, long double z1, long double x2, long double y2, long double z2, int size) {

    my_file << "                <Transform translation=\"" << 0 << " " << 0 << " " <<  0 << "\">" << std::endl;
    my_file << "                    <Shape>" << std::endl;
    my_file << "                        <Appearance>" << std::endl;
    my_file << "                            <LineProperties applied='TRUE' linewidthscalefactor='" << 2*size+1 << "'></LineProperties>" << std::endl;
    my_file << "                        </Appearance>" << std::endl;
    my_file << "                        <IndexedLineSet coordIndex='0 1'><Coordinate point='" << x1 << " " << y1 << " "  << z1 << " "  << x2  << " " << y2  << " " << z2 << "'></IndexedLineSet>" << std::endl;
    my_file << "                    </Shape>" << std::endl;
    my_file << "                </Transform>" << std::endl;
}

void WriteX3D::close_file(void) {
    // Write some final things
    my_file << "            </scene>" << std::endl;
    my_file << "        </x3d>" << std::endl;
    my_file << "    </body>" << std::endl;
    my_file << "</html>" << std::endl;

    // Close the file
    my_file.close();
}