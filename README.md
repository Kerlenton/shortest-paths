# shortest-paths

This project demonstrates the shortest paths calculation in a graph.

## Build Instructions

1. Create a build directory:
   ```
   mkdir build
   cd build
   ```

2. Generate the build system with CMake:
   ```
   cmake ..
   ```

3. Build the project:
   ```
   cmake --build .
   ```

## Run Program

After building, you can run the main executable:
```
./shortest_paths /path/to/graph.txt [bfs|floyd]
```
If no algorithm is specified, BFS will be used by default.

Examples:
```
./shortest_paths ../graph.txt
```
```
./shortest_paths ../graph.txt bfs
```
```
./shortest_paths ../graph.txt floyd
```

## Run Tests

To run the tests executable:
```
./test_shortest_paths
```
or
```
ctest
```

## Run Benchmarks

To run the tests executable:
```
./benchmarks
```
