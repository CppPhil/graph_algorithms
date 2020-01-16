# static library
add_library(
    fleury_lib
    STATIC
    reachable_test_graph.cpp
    is_bridge_test_graph.cpp
    algorithm_test_graph.cpp
    export_graph.cpp
)

target_include_directories(
    fleury_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../src
)

target_include_directories(
    fleury_lib
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR} 
)

target_include_directories(
    fleury_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../../deps/philslib/include
)

target_include_directories(
    fleury_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../../deps/optional/include
)

set_target_properties(
    fleury_lib 
    PROPERTIES
        CXX_STANDARD 17
)
