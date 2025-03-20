#pragma once

#include <istream>
#include <vector>

namespace NShortestPaths {

// Graph class holds an undirected unweighted graph.
class TGraph {
   public:
    TGraph() = default;
    void Load(std::istream& in);
    [[nodiscard]] int VerticesCount() const noexcept { return VerticesCount_; }
    [[nodiscard]] const std::vector<std::vector<int>>& AdjacencyList()
        const noexcept {
        return AdjList_;
    }

   private:
    int VerticesCount_{0};
    int EdgesCount_{0};
    std::vector<std::vector<int>> AdjList_;
};

}  // namespace NShortestPaths
