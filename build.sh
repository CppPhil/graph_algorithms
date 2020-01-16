#!/bin/bash

### This script builds the project

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Build directory
readonly BUILD_DIR=$DIR/build

# The C compiler to use
readonly C_COMPILER="gcc-8"

# The C++ compiler to use
readonly CXX_COMPILER="g++-8"

if [ "$#" -ne 1 ]; then
    echo "Illegal number of command line arguments. Enter Debug or Release as the first command line argument."
    exit 1
fi

if [ "$1" == "Debug" ] || [ "$1" == "Release" ]; then
    # Save the current working directory
    readonly previous_directory=$(pwd)

    # Change working directory to the directory containing this bash script.
    cd $DIR

    # Delete build directory
    rm -rf $BUILD_DIR

    # Generate native build scripts
    CC=$C_COMPILER CXX=$CXX_COMPILER cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=$1 -G "Unix Makefiles" $DIR

    # Go into the build directory
    cd $BUILD_DIR

    # Build
    cmake --build $BUILD_DIR -- -j2 VERBOSE=1

    # Change working directory back to the original.
    cd $previous_directory

    # Exit this bash script
    exit 0
fi

# Exit with error
echo "The first command line argument was neither Debug nor Release."
exit 1

