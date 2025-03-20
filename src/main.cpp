#include <exception>
#include <filesystem>
#include <fstream>
#include <memory>
#include <print>
#include <string>
#include <vector>

#include "breadth_first_search.hpp"
#include "breadth_first_search_parallel.hpp"
#include "floyd_warshall.hpp"
#include "floyd_warshall_parallel.hpp"
#include "graph.hpp"
#include "shortest_path_finder.hpp"

using namespace NShortestPaths;

// Prints usage information.
void PrintUsage(const char* progName) {
    std::print(stderr, "Usage: {} <graph_file> [algorithm]\n", progName);
    std::print(stderr,
               "  algorithm: bfs-seq, bfs-par, floyd-seq, or floyd-par\n");
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

    // Determine which algorithm and mode to use based on the input argument.
    std::string algoStr = (argc >= 3) ? argv[2] : "bfs-seq";
    std::unique_ptr<IShortestPathFinder> algorithm;
    if (algoStr == "bfs-seq") {
        // Use sequential BFS algorithm.
        algorithm = std::make_unique<TBreadthFirstSearch>();
    } else if (algoStr == "bfs-par") {
        // Use parallel BFS algorithm.
        algorithm = std::make_unique<TBreadthFirstSearchParallel>();
    } else if (algoStr == "floyd-seq") {
        // Use sequential Floyd–Warshall algorithm.
        algorithm = std::make_unique<TFloydWarshall>();
    } else if (algoStr == "floyd-par") {
        // Use parallel Floyd–Warshall algorithm.
        algorithm = std::make_unique<TFloydWarshallParallel>();
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
