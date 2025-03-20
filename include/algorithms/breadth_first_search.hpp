#pragma once

#include "shortest_path_finder.hpp"

namespace NShortestPaths {

// The TBreadthFirstSearch class implements the Breadth-First Search algorithm.
class TBreadthFirstSearch : public IShortestPathFinder {
   public:
    // Compute the shortest paths using BFS starting from the given vertex.
    std::vector<int> Compute(const TGraph& graph, int start) const override;
};

}  // namespace NShortestPaths
