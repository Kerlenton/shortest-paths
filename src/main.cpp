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
    if (argc < 2) {
        PrintUsage(argv[0]);
        return 1;
    }

    std::string filename = argv[1];
    if (!std::filesystem::exists(filename)) {
        std::print(stderr, "File does not exist: {}\n", filename);
        return 1;
    }

    std::ifstream in(filename);
    if (!in) {
        std::print(stderr, "Failed to open file: {}\n", filename);
        return 1;
    }

    TGraph graph;
    try {
        graph.Load(in);
    } catch (const std::exception& e) {
        std::print(stderr, "Error loading graph: {}\n", e.what());
        return 1;
    }

    int startVertex;
    if (!(in >> startVertex)) {
        std::print(stderr, "Error reading start vertex.\n");
        return 1;
    }

    std::string algoStr = (argc >= 3) ? argv[2] : "bfs";
    std::unique_ptr<IShortestPathFinder> algorithm;
    if (algoStr == "bfs") {
        algorithm = std::make_unique<TBreadthFirstSearch>();
    } else if (algoStr == "floyd") {
        algorithm = std::make_unique<TFloydWarshall>();
    } else {
        std::print(stderr, "Unknown algorithm: {}\n", algoStr);
        PrintUsage(argv[0]);
        return 1;
    }

    try {
        auto distances = algorithm->Compute(graph, startVertex);
        for (int d : distances) {
            std::print("{}\n", d);
        }
    } catch (const std::exception& e) {
        std::print(stderr, "Error computing shortest paths: {}\n", e.what());
        return 1;
    }

    return 0;
}
