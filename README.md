# Graph algorithms
This project implements various graph algorithms in C++.  

## Supported operating systems
- GNU/Linux  

## Prerequisites
- A modern GNU C++ Compiler (g++)  
- A recent release of CMake  

## Cloning
The repository must be cloned recursively to fetch the submodules.  
`git clone https://github.com/CppPhil/graph_algorithms.git --recursive` for instance.  

## Building
| What to do                                  | Bash command       |
|---------------------------------------------|--------------------|
| build application and tests in debug mode   | `./build.sh Debug`   |
| build application and tests in release mode | `./build.sh Release` |

## Running
After having built the application can be run using `./run.sh`.  

## Testing
After having built the tests can be run using `./test.sh`.  
To rebuild in debug mode before running the tests `./test.sh rebuild` can be used.  

## Formatting
The source code can be formatted using `./format.sh`.  
