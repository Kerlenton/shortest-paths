#pragma once

#include "shortest_path_finder.hpp"

namespace NShortestPaths {

class TFloydWarshall : public IShortestPathFinder {
   public:
    std::vector<int> Compute(const TGraph& graph, int start) const override;
};

}  // namespace NShortestPaths
