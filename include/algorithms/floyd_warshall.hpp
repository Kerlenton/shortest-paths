#pragma once

#include "shortest_path_finder.hpp"

namespace NShortestPaths {

// The TFloydWarshall class implements the Floyd–Warshall algorithm for shortest
// paths.
class TFloydWarshall : public IShortestPathFinder {
   public:
    // Compute the shortest paths using the Floyd–Warshall algorithm starting
    // from the given vertex.
    std::vector<int> Compute(const TGraph& graph, int start) const override;
};

}  // namespace NShortestPaths
