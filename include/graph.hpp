#pragma once

#include <istream>
#include <vector>

class [[nodiscard]] Graph {
   public:
    explicit Graph() noexcept = default;

    // Reads the graph from the input stream.
    void loadFromStream(std::istream &in);

    // Calculates the shortest distances from vertex start using width search.
    // Returns a vector where i-th element is the distance from start to vertex
    // i.
    [[nodiscard]] std::vector<int> shortestDistances(int start) const;

    // Returns the number of vertices in the graph.
    [[nodiscard]] int numVertices() const noexcept { return verticesCount; }

   private:
    int verticesCount{0};
    int edgesCount{0};
    std::vector<std::vector<int>> adjList;  // Adjacency list.
};
