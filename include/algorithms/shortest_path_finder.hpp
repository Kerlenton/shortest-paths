#pragma once

#include <vector>

#include "graph.hpp"  // теперь из include/core

namespace NShortestPaths {

class IShortestPathFinder {
   public:
    virtual std::vector<int> Compute(const TGraph& graph, int start) const = 0;
    virtual ~IShortestPathFinder() = default;
};

}  // namespace NShortestPaths
