#include "graph.hpp"

#include <stdexcept>

namespace NShortestPaths {

void TGraph::Load(std::istream& in) {
    if (!(in >> VerticesCount_)) {
        throw std::runtime_error("Failed to read number of vertices");
    }
    if (!(in >> EdgesCount_)) {
        throw std::runtime_error("Failed to read number of edges");
    }

    AdjList_.assign(VerticesCount_, {});
    for (int i = 0; i < EdgesCount_; ++i) {
        int u, v;
        if (!(in >> u >> v)) {
            throw std::runtime_error("Failed to read edge");
        }
        if (u < 0 || u >= VerticesCount_ || v < 0 || v >= VerticesCount_) {
            throw std::out_of_range("Edge vertex out of range");
        }

        AdjList_[u].push_back(v);
        AdjList_[v].push_back(u);
    }
}

}  // namespace NShortestPaths
