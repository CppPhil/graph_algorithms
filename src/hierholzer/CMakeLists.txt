# static library
add_library(
    hierholzer_lib
    STATIC
    algorithm_test_graph.cpp
    export_graph.cpp
)

target_include_directories(
    hierholzer_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../src
)

target_include_directories(
    hierholzer_lib
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR} 
)

target_include_directories(
    hierholzer_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../deps/philslib/include
)

target_include_directories(
    hierholzer_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../deps/optional/include
)

set_target_properties(
    hierholzer_lib 
    PROPERTIES
        CXX_STANDARD 17
)

target_link_libraries(
    hierholzer_lib
    graph_format_lib
)
