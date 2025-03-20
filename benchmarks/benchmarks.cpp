#include "graph.hpp"
#include "breadth_first_search.hpp"
#include "floyd_warshall.hpp"
#include "graph_factory.hpp"
#include <sstream>
#include <iostream>
#include <chrono>
#include <vector>

using namespace NShortestPaths;

int main() {
    std::cout << "Benchmarking BFS vs Floyd–Warshall algorithms\n";
    std::cout << "Graph type: random tree\n";
    std::cout << "Iterations per test: 3\n";
    std::cout << "---------------------------------------------------------------\n";
    std::cout << "Size\tBFS (ms)\tFloyd–Warshall (ms)\tRatio (FW/BFS)\n";
    std::cout << "---------------------------------------------------------------\n";

    std::vector<int> sizes = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    const int iterations = 3;
    int startVertex = 0;

    TBreadthFirstSearch bfs;
    TFloydWarshall floyd;

    for (int n : sizes) {
        auto edges = NGraphFactory::GenerateTree(n);
        std::string graphData = NGraphFactory::SerializeGraph(n, edges);
        // Append start vertex (0).
        graphData += "0\n";

        std::istringstream iss(graphData);
        TGraph graph;
        graph.Load(iss);

        double totalBFS = 0.0;
        double totalFloyd = 0.0;
        std::vector<int> bfsResult, floydResult;

        for (int i = 0; i < iterations; ++i) {
            auto startTime = std::chrono::steady_clock::now();
            bfsResult = bfs.Compute(graph, startVertex);
            auto endTime = std::chrono::steady_clock::now();
            totalBFS += std::chrono::duration<double, std::milli>(endTime - startTime).count();

            startTime = std::chrono::steady_clock::now();
            floydResult = floyd.Compute(graph, startVertex);
            endTime = std::chrono::steady_clock::now();
            totalFloyd += std::chrono::duration<double, std::milli>(endTime - startTime).count();
        }

        if (bfsResult != floydResult) {
            std::cerr << "Results mismatch for graph size " << n << "\n";
            return 1;
        }

        double avgBFS = totalBFS / iterations;
        double avgFloyd = totalFloyd / iterations;
        double ratio = (avgBFS > 0) ? (avgFloyd / avgBFS) : 0;

        std::cout << n << "\t" << avgBFS << "\t\t" << avgFloyd << "\t\t\t" << ratio << "\n";
    }

    return 0;
}
