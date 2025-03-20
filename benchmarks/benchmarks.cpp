#include <chrono>
#include <print>
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
    std::print(stdout, "Benchmarking BFS vs Floyd–Warshall algorithms\n");
    std::print(stdout, "Graph type: random tree\n");
    std::print(stdout, "Iterations per test: 3\n");

    // Print header with fixed column widths.
    std::print(
        stdout,
        "---------------------------------------------------------------\n");
    std::print(stdout, "{:>6} {:>12} {:>24} {:>16}\n", "Size", "BFS (ms)",
               "Floyd–Warshall (ms)", "Ratio (FW/BFS)");
    std::print(
        stdout,
        "---------------------------------------------------------------\n");

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
            std::print(stderr, "Results mismatch for graph size {}\n", n);
            return 1;
        }

        double avgBFS = totalBFS / iterations;
        double avgFloyd = totalFloyd / iterations;
        double ratio = (avgBFS > 0) ? (avgFloyd / avgBFS) : 0;

        // Use fixed-width formatting for output rows.
        std::print(stdout, "{:6d} {:12.3f} {:24.3f} {:16.3f}\n", n, avgBFS,
                   avgFloyd, ratio);
    }

    return 0;
}
