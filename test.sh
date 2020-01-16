#!/bin/bash

### This script runs the test executable of the project

# Directory containing this bash script.
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Build directory
readonly BUILD_DIR=$DIR/build

if [ "$1" == "rebuild" ]; then
    bash $DIR/build.sh "Debug"
fi

# Run the test executable
$BUILD_DIR/test/unit_tests

# Exit
exit 0

