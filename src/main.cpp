#include <filesystem>
#include <fstream>
#include <print>

#include "graph.hpp"

int main(int argc, char *argv[]) {
    // Check command line arguments.
    if (argc < 2) [[unlikely]] {
        std::print(stderr, "Usage: {} <file_with_graph>\n", argv[0]);
        return 1;
    }

    std::string filename = argv[1];
    if (!std::filesystem::exists(filename)) [[unlikely]] {
        std::print(stderr, "File '{}' does not exist.\n", filename);
        return 1;
    }
    std::ifstream file(filename);
    if (!file) [[unlikely]] {
        std::print(stderr, "Failed to open file: {}\n", filename);
        return 1;
    }

    Graph graph;
    try {
        // Read first the information about the graph (vertices and edges).
        graph.LoadFromStream(file);
    } catch (const std::exception &e) {
        std::print(stderr, "Error reading graph: {}\n", e.what());
        return 1;
    }

    // The last line of the file contains the number of the starting vertex.
    int startVertex;
    if (!(file >> startVertex)) [[unlikely]] {
        std::print(stderr, "Error reading a start vertex from the file.\n");
        return 1;
    }

    try {
        auto distances = graph.ShortestDistances(startVertex);
        // Output distances: for each vertex in ascending order of number.
        for (const auto &d : distances) {
            std::print(stdout, "{}\n", d);
        }
    } catch (const std::exception &e) {
        std::print(stderr, "Error when calculating shortest distances: {}\n",
                   e.what());
        return 1;
    }

    return 0;
}
