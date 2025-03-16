#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "graph.hpp"

namespace fs = std::filesystem;

// Function for searching a directory with graphs by several relative paths.
fs::path findTestGraphsDir() {
    fs::path candidates[] = {"tests/graphs", "../tests/graphs",
                             "../../tests/graphs"};
    for (auto& candidate : candidates) {
        if (fs::exists(candidate) && fs::is_directory(candidate))
            return candidate;
    }
    return "";
}

// Function for searching the directory with answers by multiple relative paths.
fs::path findTestAnswersDir() {
    fs::path candidates[] = {"tests/answers", "../tests/answers",
                             "../../tests/answers"};
    for (auto& candidate : candidates) {
        if (fs::exists(candidate) && fs::is_directory(candidate))
            return candidate;
    }
    return "";
}

std::vector<std::string> read_lines(const fs::path& filepath) {
    std::vector<std::string> lines;
    std::ifstream file(filepath);
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    return lines;
}

int main() {
    fs::path graphsDir = findTestGraphsDir();
    fs::path answersDir = findTestAnswersDir();

    if (graphsDir.empty() || !fs::is_directory(graphsDir)) {
        std::cerr << "Test graphs directory not found.\n";
        return 1;
    }
    if (answersDir.empty() || !fs::is_directory(answersDir)) {
        std::cerr << "Test answers directory not found.\n";
        return 1;
    }

    for (const auto& entry : fs::directory_iterator(graphsDir)) {
        if (entry.is_regular_file() &&
            entry.path().filename().string().find("graph_") == 0) {
            fs::path graphFile = entry.path();
            // Define the name of the file with the expected answer: replace the
            // prefix "graph_" with "answer_".
            std::string graphFilename = graphFile.filename().string();
            std::string answerFilename = "answer_" + graphFilename.substr(6);
            fs::path answerFile = answersDir / answerFilename;
            if (!fs::exists(answerFile)) {
                std::cerr << "Expected answer file not found for " << graphFile
                          << "\n";
                return 1;
            }

            // Read graph from file and run quick solution.
            std::ifstream in(graphFile);
            if (!in) {
                std::cerr << "Failed to open " << graphFile << "\n";
                return 1;
            }
            Graph graph;
            try {
                graph.loadFromStream(in);
            } catch (const std::exception& e) {
                std::cerr << "Error reading graph from " << graphFile << ": "
                          << e.what() << "\n";
                return 1;
            }
            int start;
            if (!(in >> start)) {
                std::cerr << "Failed to read start vertex from " << graphFile
                          << "\n";
                return 1;
            }
            auto distances = graph.shortestDistances(start);

            // Read the expected response.
            auto expected_lines = read_lines(answerFile);
            std::vector<int> expected;
            for (const auto& line : expected_lines) {
                expected.push_back(std::stoi(line));
            }

            if (distances.size() != expected.size()) {
                std::cerr << "Mismatch in number of vertices for " << graphFile
                          << "\n";
                return 1;
            }
            for (size_t i = 0; i < distances.size(); ++i) {
                if (distances[i] != expected[i]) {
                    std::cerr << "Mismatch for vertex " << i << " in "
                              << graphFile << ". Expected: " << expected[i]
                              << ", got: " << distances[i] << "\n";
                    return 1;
                }
            }
            std::cout << "Test passed for " << graphFile.filename() << "\n";
        }
    }
    std::cout << "All generated graph tests passed.\n";
    return 0;
}
