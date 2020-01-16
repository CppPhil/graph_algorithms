# static library
add_library(
    graph_format_lib
    STATIC
    data_structure.cpp
)

target_include_directories(
    graph_format_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../src
)

target_include_directories(
    graph_format_lib
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(
    graph_format_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../deps/philslib/include
)

target_include_directories(
    graph_format_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../deps/optional/include
)

set_target_properties(
    graph_format_lib 
    PROPERTIES
        CXX_STANDARD 17
)
