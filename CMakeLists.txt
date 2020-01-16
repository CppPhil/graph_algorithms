cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(graph_project CXX)

# guard against in-source builds and bad build-type strings
include(cmake/safeguards.cmake)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic -pedantic-errors -Wcast-align -Wcast-qual -Wfloat-equal -Wmissing-field-initializers -Wmissing-include-dirs -Wmissing-noreturn -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter -Wlogical-op -Wold-style-cast -Wformat=2 -Wduplicated-cond -Wrestrict -Wno-noexcept-type -Wno-unused-function -Wno-suggest-attribute=noreturn")        
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g -march=native -funroll-loops")
endif()

# get git hash
include(cmake/git_revision.cmake)

# project version
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# configure header file
configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/config.h.in
    ${PROJECT_BINARY_DIR}/config.h
)

add_subdirectory(src)

# fetch googletest
include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/../googletest
)

# enable testing
enable_testing()

# define tests
add_subdirectory(test)
