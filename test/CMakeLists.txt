add_executable(
    unit_tests
    append_test.cpp
    bellman_ford_test.cpp
    contains_test.cpp
    vertex_test.cpp
    edge_test.cpp
    ford_fulkerson_test.cpp
    join_test.cpp
    directed_graph_test.cpp
    dijkstra_test.cpp
    a_star_test.cpp
    grid/data_structure_test.cpp
    grid/position_kind_test.cpp
    grid/position_test.cpp
    fleury/reachable_vertices_from_test.cpp
    fleury/is_bridge_test.cpp
    fleury/algorithm_test.cpp
    hierholzer_test.cpp
)

target_link_libraries(
    unit_tests
    gtest_main
    ff_lib
    romania_lib
    nm_lib
    grid_lib
    bf_lib
    graph_format_lib
    fleury_lib
    hierholzer_lib
)

target_include_directories(
    unit_tests
    PRIVATE
        ${CMAKE_BINARY_DIR}/../src
)

target_include_directories(
    unit_tests
    PRIVATE
        ${CMAKE_BINARY_DIR}/../../deps/philslib/include
)

target_include_directories(
    unit_tests
    PRIVATE
        ${CMAKE_BINARY_DIR}/../../deps/optional/include
)

set_target_properties(
    unit_tests 
    PROPERTIES
        CXX_STANDARD 17
)

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)
