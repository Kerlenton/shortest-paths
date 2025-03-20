cmake_minimum_required(VERSION 3.15)
project(ShortestPaths CXX)

# Use the C++23 standard.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create a static library with grouped source files.
add_library(shortest_paths_lib
    src/core/graph.cpp
    src/algorithms/breadth_first_search.cpp
    src/algorithms/floyd_warshall.cpp
    src/factories/graph_factory.cpp
)

# Add the include directories for public headers.
target_include_directories(shortest_paths_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/core
        ${CMAKE_CURRENT_SOURCE_DIR}/include/algorithms
        ${CMAKE_CURRENT_SOURCE_DIR}/include/factories
)

# Main executable.
add_executable(shortest_paths
    src/main.cpp
)
target_link_libraries(shortest_paths PRIVATE shortest_paths_lib)

# Test executable.
add_executable(test_shortest_paths
    tests/test_shortest_paths.cpp
)
target_link_libraries(test_shortest_paths PRIVATE shortest_paths_lib)

# Benchmark executable.
add_executable(benchmarks
    benchmarks/benchmarks.cpp
)
target_link_libraries(benchmarks PRIVATE shortest_paths_lib)

# Enable testing in CMake.
enable_testing()
# Register the test executable as a CTest test.
add_test(NAME ShortestPathsTests COMMAND test_shortest_paths)
