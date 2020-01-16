#!/bin/bash

### This script runs the main executable of the project

# Directory containing this bash script.
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Build directory
readonly BUILD_DIR=$DIR/build

readonly PREV_DIR=$(pwd)

cd $DIR

# Run the executable
$BUILD_DIR/src/executable

cd $PREV_DIR

# Exit
exit 0

