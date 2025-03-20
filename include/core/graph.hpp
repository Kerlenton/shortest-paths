#pragma once

#include <istream>
#include <span>
#include <vector>

namespace NShortestPaths {

// Graph class holds an undirected unweighted graph.
class TGraph {
   public:
    // Default constructor.
    TGraph() = default;

    // Load the graph data from an input stream.
    void Load(std::istream& in);

    // Get the number of vertices in the graph.
    [[nodiscard]] int VerticesCount() const noexcept { return VerticesCount_; }
    // Get the adjacency list representing graph connections.
    [[nodiscard]] std::span<const std::vector<int>> AdjacencyList()
        const noexcept {
        return std::span(AdjList_);
    }

   private:
    // Number of vertices in the graph.
    int VerticesCount_{0};
    // Number of edges in the graph.
    int EdgesCount_{0};
    // Adjacency list for storing edges.
    std::vector<std::vector<int>> AdjList_;
};

}  // namespace NShortestPaths
