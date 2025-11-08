#!/bin/bash
# Exit immediately if a command exits with a non-zero status.
set -e

# Create a build directory and navigate into it.
mkdir -p build
cd build

# Configure the project with CMake, specifying a Release build type for optimizations.
cmake -DCMAKE_BUILD_TYPE=Release ..

# Compile the project using all available CPU cores.
make -j$(nproc)

echo "Build complete! The executable is at build/imguipm"
