#include "breadth_first_search_parallel.hpp"

#include <algorithm>
#include <mutex>
#include <span>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace NShortestPaths {

std::vector<int> TBreadthFirstSearchParallel::Compute(const TGraph& graph,
                                                      int start) const {
    int n = graph.VerticesCount();
    // Validate the starting vertex.
    if (start < 0 || start >= n) {
        throw std::out_of_range("Invalid starting vertex");
    }

    // Initialize distances with -1 to indicate unvisited vertices.
    std::vector<int> distances(n, -1);
    // Vector for the current level.
    std::vector<int> current;
    current.push_back(start);
    distances[start] = 0;
    int level = 0;

    // Determine the number of threads to use.
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) {
        numThreads = 2;
    }

    // Level-synchronous BFS.
    while (!current.empty()) {
        std::vector<int> next;
        std::mutex nextMutex;
        std::vector<std::thread> threads;
        size_t total = current.size();
        size_t chunkSize = (total + numThreads - 1) / numThreads;

        // Launch threads processing chunks of the current level.
        for (unsigned int t = 0; t < numThreads; t++) {
            size_t begin = t * chunkSize;
            if (begin >= total) break;
            size_t end = std::min(begin + chunkSize, total);

            threads.emplace_back([&, begin, end, level]() {
                std::vector<int> localNext;
                for (size_t i = begin; i < end; i++) {
                    int u = current[i];
                    // Iterate over all neighbors.
                    for (auto v : graph.AdjacencyList()[u]) {
                        // First check without locking.
                        if (distances[v] == -1) {
                            // Critical section to update shared data.
                            std::lock_guard<std::mutex> lock(nextMutex);
                            if (distances[v] == -1) {
                                distances[v] = level + 1;
                                localNext.push_back(v);
                            }
                        }
                    }
                }

                // Merge local results.
                if (!localNext.empty()) {
                    std::lock_guard<std::mutex> lock(nextMutex);
                    next.insert(next.end(), localNext.begin(), localNext.end());
                }
            });
        }

        // Join all threads.
        for (auto& th : threads) {
            th.join();
        }

        current = std::move(next);
        ++level;
    }

    return distances;
}

}  // namespace NShortestPaths
