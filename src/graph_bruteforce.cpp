#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file_with_graph>\n";
        return 1;
    }
    std::string filename = argv[1];
    if (!std::filesystem::exists(filename)) {
        std::cerr << "File '" << filename << "' does not exist.\n";
        return 1;
    }
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return 1;
    }

    int verticesCount, edgesCount;
    if (!(file >> verticesCount)) {
        std::cerr << "Error reading number of vertices.\n";
        return 1;
    }
    if (!(file >> edgesCount)) {
        std::cerr << "Error reading number of edges.\n";
        return 1;
    }

    // Initialization of distance matrix.
    const int INF = std::numeric_limits<int>::max() / 2;
    std::vector<std::vector<int>> dist(verticesCount,
                                       std::vector<int>(verticesCount, INF));
    for (int i = 0; i < verticesCount; ++i) {
        dist[i][i] = 0;
    }

    // Read edges and fill matrix.
    for (int i = 0; i < edgesCount; ++i) {
        int u, v;
        if (!(file >> u >> v)) {
            std::cerr << "Error reading edge " << i << ".\n";
            return 1;
        }
        if (u < 0 || u >= verticesCount || v < 0 || v >= verticesCount) {
            std::cerr << "Invalid vertex number in edge " << i << ".\n";
            return 1;
        }
        // The graph is undirected, edge length is equal to 1.
        dist[u][v] = 1;
        dist[v][u] = 1;
    }

    int start;
    if (!(file >> start)) {
        std::cerr << "Error reading starting vertex.\n";
        return 1;
    }
    if (start < 0 || start >= verticesCount) {
        std::cerr << "Starting vertex out of range.\n";
        return 1;
    }

    // Floyd-Worshell Algorithm.
    for (int k = 0; k < verticesCount; ++k) {
        for (int i = 0; i < verticesCount; ++i) {
            for (int j = 0; j < verticesCount; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Output the shortest distances from the start vertex.
    for (int i = 0; i < verticesCount; ++i) {
        int d = (dist[start][i] >= INF) ? -1 : dist[start][i];
        std::cout << d << "\n";
    }

    return 0;
}
