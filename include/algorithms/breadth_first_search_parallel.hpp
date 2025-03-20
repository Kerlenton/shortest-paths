#pragma once

#include "shortest_path_finder.hpp"

namespace NShortestPaths {

// The TBreadthFirstSearchParallel class implements the parallel Breadth-First
// Search algorithm.
class TBreadthFirstSearchParallel : public IShortestPathFinder {
   public:
    // Compute the shortest paths using parallel BFS starting from the given
    // vertex.
    std::vector<int> Compute(const TGraph& graph, int start) const override;
};

}  // namespace NShortestPaths
