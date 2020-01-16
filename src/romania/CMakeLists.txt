# static library
add_library(romania_lib STATIC city.cpp create_graph.cpp heuristic.cpp)

target_include_directories(
    romania_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../src
)

target_include_directories(
    romania_lib
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(
    romania_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../deps/philslib/include
)

target_include_directories(
    romania_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../deps/optional/include
)

set_target_properties(
    romania_lib 
    PROPERTIES
        CXX_STANDARD 17
)
