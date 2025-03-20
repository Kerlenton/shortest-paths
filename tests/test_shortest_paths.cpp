#include <cassert>
#include <exception>
#include <print>
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
    // Load the graph.
    graph.Load(iss);
    int startVertex;
    // Read the start vertex separately.
    iss >> startVertex;

    // Create algorithm instances.
    TBreadthFirstSearch bfs_seq;
    TBreadthFirstSearchParallel bfs_par;
    TFloydWarshall floyd_seq;
    TFloydWarshallParallel floyd_par;

    // Compute distances using both sequential and parallel algorithms.
    auto bfsResultSeq = bfs_seq.Compute(graph, startVertex);
    auto bfsResultPar = bfs_par.Compute(graph, startVertex);
    auto floydResultSeq = floyd_seq.Compute(graph, startVertex);
    auto floydResultPar = floyd_par.Compute(graph, startVertex);

    // Assert that all algorithms produce the same result.
    assert(bfsResultSeq == bfsResultPar);
    assert(bfsResultSeq == floydResultSeq);
    assert(bfsResultSeq == floydResultPar);
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
