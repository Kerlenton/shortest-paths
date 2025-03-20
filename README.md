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
./shortest_paths /path/to/graph.txt [bfs-seq|bfs-par|floyd-seq|floyd-par]
```
If no algorithm is specified, sequential BFS will be used by default.

Examples:
```
./shortest_paths ../graph.txt
```
```
./shortest_paths ../graph.txt bfs-seq
```
```
./shortest_paths ../graph.txt bfs-par
```
```
./shortest_paths ../graph.txt floyd-seq
```
```
./shortest_paths ../graph.txt floyd-par
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

To run the benchmarks executable:
```
./benchmarks
```
