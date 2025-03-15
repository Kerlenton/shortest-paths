#include <fstream>
#include <iostream>

#include "graph.hpp"

int main(int argc, char *argv[]) {
    // Check command line arguments.
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file_with_graph>\n";
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return 1;
    }

    Graph graph;
    try {
        // // Read first the information about the graph (vertices and edges).
        graph.loadFromStream(file);
    } catch (const std::exception &e) {
        std::cerr << "Error reading graph: " << e.what() << "\n";
        return 1;
    }

    // The last line of the file contains the number of the starting vertex.
    int startVertex;
    if (!(file >> startVertex)) {
        std::cerr << "Error reading a start vertex from a file.\n";
        return 1;
    }

    try {
        auto distances = graph.shortestDistances(startVertex);
        // Output distances: for each vertex in ascending order of number.
        for (const auto &d : distances) {
            std::cout << d << "\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Error when calculating shortest distances: " << e.what()
                  << "\n";
        return 1;
    }

    return 0;
}
