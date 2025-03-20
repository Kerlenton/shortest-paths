#pragma once

#include "shortest_path_finder.hpp"

namespace NShortestPaths {

// The TFloydWarshallParallel class implements the parallel Floyd–Warshall
// algorithm.
class TFloydWarshallParallel : public IShortestPathFinder {
   public:
    // Compute the shortest paths using the parallel Floyd–Warshall algorithm
    // starting from the given vertex.
    std::vector<int> Compute(const TGraph& graph, int start) const override;
};

}  // namespace NShortestPaths
