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
    // Print introductory information for the benchmark.
    std::print(stdout, "Benchmarking BFS vs Floyd–Warshall algorithms\n");
    std::print(stdout, "Graph type: random tree\n");
    std::print(stdout, "Iterations per test: 3\n");

    // Print a header with fixed column widths for the benchmark results.
    std::print(
        stdout,
        "---------------------------------------------------------------\n");
    std::print(stdout, "{:>6} {:>12} {:>24} {:>16}\n", "Size", "BFS (ms)",
               "Floyd–Warshall (ms)", "Ratio (FW/BFS)");
    std::print(
        stdout,
        "---------------------------------------------------------------\n");

    // Define various graph sizes to be tested.
    std::vector<int> sizes = {100, 200, 300, 400, 500,
                              600, 700, 800, 900, 1000};
    // Number of iterations per test.
    constexpr int iterations = 3;
    // The starting vertex for path computation.
    int startVertex = 0;

    // Instance of the BFS algorithm.
    TBreadthFirstSearch bfs;
    // Instance of the Floyd–Warshall algorithm.
    TFloydWarshall floyd;

    // Lambda function to measure the execution time of a function.
    auto measure = [&](auto&& func) -> double {
        auto startTime = std::chrono::steady_clock::now();
        func();
        auto endTime = std::chrono::steady_clock::now();
        return std::chrono::duration<double, std::milli>(endTime - startTime)
            .count();
    };

    // Run benchmarks for each graph size.
    for (const auto& n : sizes) {
        // Generate a random tree.
        auto edges = NGraphFactory::GenerateTree(n);
        // Serialize the graph.
        std::string graphData = NGraphFactory::SerializeGraph(n, edges);
        // Append start vertex 0.
        graphData += "0\n";

        // Create an input stream from the graph data.
        std::istringstream iss(graphData);
        TGraph graph;
        // Load the graph.
        graph.Load(iss);

        double totalBFS = 0.0;
        double totalFloyd = 0.0;
        std::vector<int> bfsResult, floydResult;

        // Measure the execution time for both algorithms over several
        // iterations.
        for (int i = 0; i < iterations; ++i) {
            totalBFS +=
                measure([&] { bfsResult = bfs.Compute(graph, startVertex); });
            totalFloyd += measure(
                [&] { floydResult = floyd.Compute(graph, startVertex); });
        }

        // Check that both algorithms produced the same result.
        if (bfsResult != floydResult) {
            std::print(stderr, "Results mismatch for graph size {}\n", n);
            return 1;
        }

        // Calculate the average execution time and the ratio.
        double avgBFS = totalBFS / iterations;
        double avgFloyd = totalFloyd / iterations;
        double ratio = (avgBFS > 0) ? (avgFloyd / avgBFS) : 0;

        // Print the benchmark results in a formatted manner.
        std::print(stdout, "{:6d} {:12.3f} {:24.3f} {:16.3f}\n", n, avgBFS,
                   avgFloyd, ratio);
    }

    return 0;
}
