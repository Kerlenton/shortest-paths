#include <cassert>
#include <exception>
#include <print>
#include <sstream>
#include <string>
#include <vector>

#include "breadth_first_search.hpp"
#include "floyd_warshall.hpp"
#include "graph.hpp"
#include "graph_factory.hpp"

using namespace NShortestPaths;

// Runs a test for a randomly generated tree of size n.
void runTest(int n) {
    // Generate a random tree.
    auto edges = NGraphFactory::GenerateTree(n);
    // Serialize the graph.
    std::string graphData = NGraphFactory::SerializeGraph(n, edges);
    // Append the start vertex 0 as the last line.
    graphData += "0\n";

    // Create an input stream from the graph data.
    std::istringstream iss(graphData);
    TGraph graph;
    // Load the graph from the input stream.
    graph.Load(iss);
    int startVertex;
    // Read the start vertex separately.
    iss >> startVertex;

    // Create a BFS algorithm instance.
    TBreadthFirstSearch bfs;
    // Create a Floyd–Warshall algorithm instance.
    TFloydWarshall floyd;
    // Compute distances using BFS.
    auto bfsResult = bfs.Compute(graph, startVertex);
    // Compute distances using Floyd–Warshall.
    auto floydResult = floyd.Compute(graph, startVertex);

    // Assert that both algorithms produce the same result.
    assert(bfsResult == floydResult);
}

int main() {
    try {
        // Run tests for graph sizes ranging from 2 to 50.
        for (int n = 2; n <= 50; ++n) {
            runTest(n);
        }
        // Print success message.
        std::print(stdout, "All tests passed.\n");
    } catch (const std::exception& e) {
        // Print error message if test fails.
        std::print(stderr, "Test failed: {}\n", e.what());
        return 1;
    }
    return 0;
}
