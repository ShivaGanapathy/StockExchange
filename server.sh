#!/bin/bash


# Run CMake in the build directory
cd build
cmake .

# Build the executable using make
make

# Copy the executable to the root directory
cp -f ./server ../

# Run the executable from the root directory
cd ..

# Clear output before running the server
clear

./server
