#include <exception>
#include <filesystem>
#include <fstream>
#include <memory>
#include <print>
#include <string>
#include <vector>

#include "breadth_first_search.hpp"
#include "floyd_warshall.hpp"
#include "graph.hpp"
#include "shortest_path_finder.hpp"

using namespace NShortestPaths;

// Prints usage information.
void PrintUsage(const char* progName) {
    std::print(stderr, "Usage: {} <graph_file> [algorithm]\n", progName);
    std::print(stderr, "  algorithm: bfs (default) or floyd\n");
}

int main(int argc, char* argv[]) {
    // Check if the user provided the required arguments.
    if (argc < 2) {
        PrintUsage(argv[0]);
        return 1;
    }

    std::string filename = argv[1];
    // Verify that the specified file exists.
    if (!std::filesystem::exists(filename)) {
        std::print(stderr, "File does not exist: {}\n", filename);
        return 1;
    }

    std::ifstream in(filename);
    // Verify that the file was opened successfully.
    if (!in) {
        std::print(stderr, "Failed to open file: {}\n", filename);
        return 1;
    }

    TGraph graph;
    try {
        // Load the graph from the file.
        graph.Load(in);
    } catch (const std::exception& e) {
        std::print(stderr, "Error loading graph: {}\n", e.what());
        return 1;
    }

    int startVertex;
    // Read the start vertex from the input stream.
    if (!(in >> startVertex)) {
        std::print(stderr, "Error reading start vertex.\n");
        return 1;
    }

    // Determine which algorithm to use based on the input argument.
    std::string algoStr = (argc >= 3) ? argv[2] : "bfs";
    std::unique_ptr<IShortestPathFinder> algorithm;
    if (algoStr == "bfs") {
        // Use BFS algorithm.
        algorithm = std::make_unique<TBreadthFirstSearch>();
    } else if (algoStr == "floyd") {
        // Use Floyd–Warshall algorithm.
        algorithm = std::make_unique<TFloydWarshall>();
    } else {
        std::print(stderr, "Unknown algorithm: {}\n", algoStr);
        PrintUsage(argv[0]);
        return 1;
    }

    try {
        // Compute the shortest paths from the start vertex.
        auto distances = algorithm->Compute(graph, startVertex);
        // Output the computed distances.
        for (const auto& d : distances) {
            std::print("{}\n", d);
        }
    } catch (const std::exception& e) {
        std::print(stderr, "Error computing shortest paths: {}\n", e.what());
        return 1;
    }

    return 0;
}
