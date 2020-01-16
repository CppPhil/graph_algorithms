# static library
add_library(ff_lib STATIC create_graph.cpp)

target_include_directories(
    ff_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../src
)

target_include_directories(
    ff_lib
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(
    ff_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../../deps/philslib/include
)

target_include_directories(
    ff_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../../deps/optional/include
)

set_target_properties(
    ff_lib 
    PROPERTIES
        CXX_STANDARD 17
)
