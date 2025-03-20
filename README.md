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

## Run Tests

To run the tests executable:
```
./test_shortest_paths
```

## Run Benchmarks

To run the tests executable:
```
./benchmarks
```
