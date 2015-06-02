#!/bin/bash

# Clean the build directory
cd ..
rm -rf build

# Make a new one
mkdir build
cd build

# Build the project
cmake ..
make

cd ..

exit 0