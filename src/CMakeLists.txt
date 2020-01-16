add_subdirectory(ford_fulkerson)
add_subdirectory(romania)
add_subdirectory(nm)
add_subdirectory(grid)
add_subdirectory(bellman_ford)
add_subdirectory(graph_format)
add_subdirectory(fleury)
add_subdirectory(hierholzer)

# compile main executable
add_executable(executable main.cpp)

target_include_directories(
    executable
    PRIVATE
        ${PROJECT_BINARY_DIR}
)

target_include_directories(
    executable
    PRIVATE
        ${CMAKE_BINARY_DIR}/../deps/philslib/include
)

target_include_directories(
    executable
    PRIVATE
        ${CMAKE_BINARY_DIR}/../deps/optional/include
)

set_target_properties(
    executable 
    PROPERTIES
        CXX_STANDARD 17
)

# link library
target_link_libraries(
    executable
    ff_lib
    romania_lib
    nm_lib
    grid_lib
    bf_lib
    graph_format_lib
    fleury_lib
    hierholzer_lib
)
