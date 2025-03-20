# shortest-paths

This project demonstrates the shortest paths calculation in a graph.

## Requirements

- CMake: Version 3.15 or higher.
- Compiler: A C++ compiler with C++23 support.
- Build Tools: Standard build tools (e.g., make, Ninja, or Visual Studio).

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
./shortest_paths <graph_file> [algorithm]
```

Where:
- **<graph_file>**: Path to a text file containing the graph data. The file should be formatted as follows:
  - The **first line** specifies the number of vertices.
  - The **second line** specifies the number of edges.
  - The **subsequent lines** list each edge in the format `u v` (where `u` and `v` are vertex indices).
  - The **final line** indicates the starting vertex for the algorithm.

- **[algorithm]** (Optional): Specifies which algorithm to use. Available options are:
  - **bfs-seq** — Sequential Breadth-First Search (default if not specified).
  - **bfs-par** — Parallel Breadth-First Search.
  - **floyd-seq** — Sequential Floyd–Warshall.
  - **floyd-par** — Parallel Floyd–Warshall.

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

## Contact

You can reach me through the following channels:

- **VK:** [vk.com/kerlenton](https://vk.com/kerlenton)
- **Telegram:** [@krlntn](https://t.me/krlntn)
- **Email:** [semyonschv@yandex.ru](mailto:semyonschv@yandex.ru)
