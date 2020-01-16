# static library
add_library(
    grid_lib
    STATIC
    column.cpp
    create.cpp
    data_structure.cpp
    position_kind.cpp
    position.cpp
    row.cpp
    manhattan_distance.cpp
)

target_include_directories(
    grid_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../src
)

target_include_directories(
    grid_lib
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(
    grid_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../deps/philslib/include
)

target_include_directories(
    grid_lib
    PRIVATE
        ${CMAKE_BINARY_DIR}/../deps/optional/include
)

set_target_properties(
    grid_lib 
    PROPERTIES
        CXX_STANDARD 17
)
