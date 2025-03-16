cmake_minimum_required(VERSION 3.15)
project(ShortestPaths CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable file
add_executable(shortest_paths src/main.cpp src/graph.cpp)
target_include_directories(shortest_paths PRIVATE include)
target_compile_features(shortest_paths PRIVATE cxx_std_23)

# Brute-force executable for verifying small graphs
add_executable(graph_bruteforce src/graph_bruteforce.cpp)
target_include_directories(graph_bruteforce PRIVATE include)
target_compile_features(graph_bruteforce PRIVATE cxx_std_23)

# Generated tests using pre-generated graphs and answers
add_executable(generated_tests tests/test_generated_graphs.cpp src/graph.cpp)
target_include_directories(generated_tests PRIVATE include)
target_compile_features(generated_tests PRIVATE cxx_std_23)

enable_testing()
add_test(NAME GeneratedTests COMMAND generated_tests)
