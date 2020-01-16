# static library
add_library(nm_lib STATIC identifiers.cpp create_graph.cpp heuristic.cpp)

target_include_directories(
    nm_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../src
)

target_include_directories(
    nm_lib
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(
    nm_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../../deps/philslib/include
)

target_include_directories(
    nm_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../../deps/optional/include
)

set_target_properties(
    nm_lib 
    PROPERTIES
        CXX_STANDARD 17
)
