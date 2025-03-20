#pragma once

#include <vector>

#include "graph.hpp"

namespace NShortestPaths {

// The IShortestPathFinder interface defines the method for computing shortest
// paths.
class IShortestPathFinder {
   public:
    // Compute the shortest path distances from the given starting vertex.
    [[nodiscard]] virtual std::vector<int> Compute(const TGraph& graph,
                                                   int start) const = 0;
    // Virtual destructor for proper cleanup.
    virtual ~IShortestPathFinder() = default;
};

}  // namespace NShortestPaths
