#include <chrono>
#include <iostream>
#include <ratio>
#include <sstream>
#include <string>
#include <vector>

#include "breadth_first_search.hpp"
#include "floyd_warshall.hpp"
#include "graph.hpp"
#include "graph_factory.hpp"

using namespace NShortestPaths;

int main() {
    std::cout << "Benchmarking BFS vs Floyd–Warshall algorithms\n";
    std::cout << "Graph type: random tree\n";
    std::cout << "Iterations per test: 3\n";
    std::cout
        << "---------------------------------------------------------------\n";
    std::cout << "Size\tBFS (ms)\tFloyd–Warshall (ms)\tRatio (FW/BFS)\n";
    std::cout
        << "---------------------------------------------------------------\n";

    std::vector<int> sizes = {100, 200, 300, 400, 500,
                              600, 700, 800, 900, 1000};
    constexpr int iterations = 3;
    int startVertex = 0;

    TBreadthFirstSearch bfs;
    TFloydWarshall floyd;

    auto measure = [&](auto&& func) -> double {
        auto startTime = std::chrono::steady_clock::now();
        func();
        auto endTime = std::chrono::steady_clock::now();
        return std::chrono::duration<double, std::milli>(endTime - startTime)
            .count();
    };

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
            totalBFS +=
                measure([&] { bfsResult = bfs.Compute(graph, startVertex); });
            totalFloyd += measure(
                [&] { floydResult = floyd.Compute(graph, startVertex); });
        }

        if (bfsResult != floydResult) {
            std::cerr << "Results mismatch for graph size " << n << "\n";
            return 1;
        }

        double avgBFS = totalBFS / iterations;
        double avgFloyd = totalFloyd / iterations;
        double ratio = (avgBFS > 0) ? (avgFloyd / avgBFS) : 0;

        std::cout << n << "\t" << avgBFS << "\t\t" << avgFloyd << "\t\t\t"
                  << ratio << "\n";
    }

    return 0;
}
