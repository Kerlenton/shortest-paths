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
./shortest_paths /path/to/graph.txt
```

## Run Tests

To run the tests executable:
```
./generated_tests
```

## Generate Test Data

To generate the test data, run the generator from the project root:
```
./tools/generate_graphs.py
```
