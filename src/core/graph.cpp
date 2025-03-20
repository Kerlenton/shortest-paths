#include "graph.hpp"

#include <stdexcept>

namespace NShortestPaths {

void TGraph::Load(std::istream& in) {
    // Read the number of vertices.
    if (!(in >> VerticesCount_)) {
        throw std::runtime_error("Failed to read number of vertices");
    }
    // Read the number of edges.
    if (!(in >> EdgesCount_)) {
        throw std::runtime_error("Failed to read number of edges");
    }

    // Initialize the adjacency list with the appropriate number of vertices.
    AdjList_.assign(VerticesCount_, {});
    for (int i = 0; i < EdgesCount_; ++i) {
        int u, v;
        // Read an edge from the input stream.
        if (!(in >> u >> v)) {
            throw std::runtime_error("Failed to read edge");
        }
        // Validate that the vertices are within valid bounds.
        if (u < 0 || u >= VerticesCount_ || v < 0 || v >= VerticesCount_) {
            throw std::out_of_range("Edge vertex out of range");
        }

        // Add the edge to the adjacency list for both vertices.
        AdjList_[u].push_back(v);
        AdjList_[v].push_back(u);
    }
}

}  // namespace NShortestPaths
