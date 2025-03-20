#include <chrono>
#include <print>
#include <ratio>
#include <sstream>
#include <string>
#include <vector>

#include "breadth_first_search.hpp"
#include "breadth_first_search_parallel.hpp"
#include "floyd_warshall.hpp"
#include "floyd_warshall_parallel.hpp"
#include "graph.hpp"
#include "graph_factory.hpp"

using namespace NShortestPaths;

int main() {
    // Print introductory information for the benchmark.
    std::print(stdout, "Benchmarking Algorithms (Sequential and Parallel).\n");
    std::print(stdout, "Graph type: random tree.\n");
    std::print(stdout, "Iterations per test: 3.\n");
    std::print(
        stdout,
        "---------------------------------------------------------------\n");
    std::print(stdout, "{:>6} {:>12} {:>12} {:>12} {:>12}\n", "Size", "BFS_seq",
               "BFS_par", "Floyd_seq", "Floyd_par");
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

    // Create algorithm instances.
    TBreadthFirstSearch bfsSeq;
    TBreadthFirstSearchParallel bfsPar;
    TFloydWarshall floydSeq;
    TFloydWarshallParallel floydPar;

    // Lambda function to measure execution time.
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

        double totalBFSSeq = 0.0, totalBFSPar = 0.0;
        double totalFloydSeq = 0.0, totalFloydPar = 0.0;
        std::vector<int> resultBFSSeq, resultBFSPar, resultFloydSeq,
            resultFloydPar;

        // Measure execution time for all algorithms.
        for (int i = 0; i < iterations; ++i) {
            totalBFSSeq += measure(
                [&] { resultBFSSeq = bfsSeq.Compute(graph, startVertex); });
            totalBFSPar += measure(
                [&] { resultBFSPar = bfsPar.Compute(graph, startVertex); });
            totalFloydSeq += measure(
                [&] { resultFloydSeq = floydSeq.Compute(graph, startVertex); });
            totalFloydPar += measure(
                [&] { resultFloydPar = floydPar.Compute(graph, startVertex); });
        }

        // Check that all algorithms produced the same result.
        if (resultBFSSeq != resultBFSPar || resultBFSSeq != resultFloydSeq ||
            resultBFSSeq != resultFloydPar) {
            std::print(stderr, "Results mismatch for graph size {}\n", n);
            return 1;
        }

        // Calculate average execution times.
        double avgBFSSeq = totalBFSSeq / iterations;
        double avgBFSPar = totalBFSPar / iterations;
        double avgFloydSeq = totalFloydSeq / iterations;
        double avgFloydPar = totalFloydPar / iterations;

        // Print benchmark results.
        std::print(stdout, "{:6d} {:12.3f} {:12.3f} {:12.3f} {:12.3f}\n", n,
                   avgBFSSeq, avgBFSPar, avgFloydSeq, avgFloydPar);
    }

    return 0;
}
