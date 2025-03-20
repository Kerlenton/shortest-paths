#include <cassert>
#include <iostream>
#include <sstream>

#include "breadth_first_search.hpp"
#include "floyd_warshall.hpp"
#include "graph.hpp"
#include "graph_factory.hpp"

using namespace NShortestPaths;

// Runs a test for a randomly generated tree of size n.
void runTest(int n) {
    auto edges = NGraphFactory::GenerateTree(n);
    std::string graphData = NGraphFactory::SerializeGraph(n, edges);
    // Append the start vertex (0) as the last line.
    graphData += "0\n";

    std::istringstream iss(graphData);
    TGraph graph;
    graph.Load(iss);
    int startVertex;
    iss >> startVertex;  // Start vertex is read separately.

    TBreadthFirstSearch bfs;
    TFloydWarshall floyd;
    auto bfsResult = bfs.Compute(graph, startVertex);
    auto floydResult = floyd.Compute(graph, startVertex);

    assert(bfsResult == floydResult);
}

int main() {
    try {
        for (int n = 2; n <= 50; ++n) {
            runTest(n);
        }
        std::cout << "All tests passed.\n";
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
