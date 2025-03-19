#pragma once

#include <istream>
#include <vector>

class [[nodiscard]] Graph {
   public:
    explicit Graph() noexcept = default;

    // Reads the graph from the input stream.
    void LoadFromStream(std::istream &in);

    // Calculates the shortest distances from vertex start using width search.
    // Returns a vector where i-th element is the distance from start to vertex
    // i.
    [[nodiscard]] std::vector<int> ShortestDistances(int start) const;

    // Returns the number of vertices in the graph.
    [[nodiscard]] int NumVertices() const noexcept { return VerticesCount_; }

   private:
    int VerticesCount_{0};
    int EdgesCount_{0};
    std::vector<std::vector<int>> AdjList_;  // Adjacency list.
};
