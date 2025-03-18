cmake_minimum_required(VERSION 3.15)
project(ShortestPaths CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common settings for all targets
add_library(common_settings INTERFACE)
target_compile_features(common_settings INTERFACE cxx_std_23)
target_include_directories(common_settings INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Main executable file
add_executable(shortest_paths src/main.cpp src/graph.cpp)
target_link_libraries(shortest_paths PRIVATE common_settings)

# Brute-force executable for verifying small graphs
add_executable(graph_bruteforce src/graph_bruteforce.cpp)
target_link_libraries(graph_bruteforce PRIVATE common_settings)

# Generated tests using pre-generated graphs and answers
add_executable(generated_tests tests/test_generated_graphs.cpp src/graph.cpp)
target_link_libraries(generated_tests PRIVATE common_settings)

enable_testing()
add_test(NAME GeneratedTests COMMAND generated_tests)
