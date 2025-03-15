cmake_minimum_required(VERSION 3.15)
project(ShortestPaths CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable file
add_executable(shortest_paths src/main.cpp src/graph.cpp)
target_include_directories(shortest_paths PRIVATE include)
