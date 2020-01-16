# static library
add_library(
    bf_lib 
    STATIC 
    negative_edge_graph.cpp
    negative_cycle.cpp
    positive_cycle.cpp
)

target_include_directories(
    bf_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../src
)

target_include_directories(
    bf_lib
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR} 
)

target_include_directories(
    bf_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../../deps/philslib/include
)

target_include_directories(
    bf_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../../deps/optional/include
)

set_target_properties(
    bf_lib 
    PROPERTIES
        CXX_STANDARD 17
)
