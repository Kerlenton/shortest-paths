#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "breadth_first_search.hpp"
#include "floyd_warshall.hpp"
#include "graph.hpp"

using namespace NShortestPaths;

// Prints usage information.
void printUsage(const char* progName) {
    std::cerr << std::format("Usage: {} <graph_file> [algorithm]\n", progName);
    std::cerr << "  algorithm: bfs (default) or floyd\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    std::string filename = argv[1];
    if (!std::filesystem::exists(filename)) {
        std::cerr << std::format("File does not exist: {}\n", filename);
        return 1;
    }

    std::ifstream in(filename);
    if (!in) {
        std::cerr << std::format("Failed to open file: {}\n", filename);
        return 1;
    }

    TGraph graph;
    try {
        graph.Load(in);
    } catch (const std::exception& e) {
        std::cerr << std::format("Error loading graph: {}\n", e.what());
        return 1;
    }

    int startVertex;
    if (!(in >> startVertex)) {
        std::cerr << "Error reading start vertex.\n";
        return 1;
    }

    std::string algoStr = (argc >= 3) ? argv[2] : "bfs";
    std::unique_ptr<IShortestPathFinder> algorithm;
    if (algoStr == "bfs") {
        algorithm = std::make_unique<TBreadthFirstSearch>();
    } else if (algoStr == "floyd") {
        algorithm = std::make_unique<TFloydWarshall>();
    } else {
        std::cerr << std::format("Unknown algorithm: {}\n", algoStr);
        printUsage(argv[0]);
        return 1;
    }

    try {
        auto distances = algorithm->Compute(graph, startVertex);
        for (int d : distances) {
            std::cout << std::format("{}\n", d);
        }
    } catch (const std::exception& e) {
        std::cerr << std::format("Error computing shortest paths: {}\n",
                                 e.what());
        return 1;
    }

    return 0;
}
