#include <cassert>
#include <format>
#include <functional>
#include <iostream>
#include <print>
#include <ranges>
#include <source_location>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "graph.hpp"

// Use std::string_view for a cleaner interface.
std::vector<int> runGraphTest(std::string_view input, int start) {
    std::string s(input);
    std::istringstream ss(s);
    Graph graph;
    graph.loadFromStream(ss);
    return graph.shortestDistances(start);
}

void testValidGraph() {
    const std::string_view input = R"(
5
4
0 1
0 4
1 2
1 3
0
)";
    auto distances = runGraphTest(input, 0);
    assert(distances[0] == 0);
    assert(distances[1] == 1);
    assert(distances[4] == 1);
    assert(distances[2] == 2);
    assert(distances[3] == 2);
}

void testInvalidInput() {
    const std::string_view input = "invalid input";
    try {
        runGraphTest(input, 0);
        assert(false && "Expected exception (runtime_error) not thrown");
    } catch (const std::runtime_error&) {
        // expected exception caught
    }
}

void testOutOfRangeStart() {
    const std::string_view input = R"(
3
2
0 1
1 2
0
)";
    try {
        runGraphTest(input, 5);
        assert(false && "Expected exception (out_of_range) not thrown");
    } catch (const std::out_of_range&) {
        // expected exception caught
    }
}

void testSingleVertex() {
    const std::string_view input = R"(
1
0
0
)";
    auto distances = runGraphTest(input, 0);
    assert(distances.size() == 1);
    assert(distances[0] == 0);
}

void testDisconnectedGraph() {
    const std::string_view input = R"(
4
1
0 1
0
)";
    auto distances = runGraphTest(input, 0);
    assert(distances[0] == 0);
    assert(distances[1] == 1);
    assert(distances[2] == -1);
    assert(distances[3] == -1);
}

void testCompleteGraph() {
    const std::string_view input = R"(
4
6
0 1
0 2
0 3
1 2
1 3
2 3
0
)";
    auto distances = runGraphTest(input, 0);
    assert(distances[0] == 0);
    assert(distances[1] == 1);
    assert(distances[2] == 1);
    assert(distances[3] == 1);
}

void testSelfLoop() {
    const std::string_view input = R"(
3
3
0 0
0 1
1 2
0
)";
    auto distances = runGraphTest(input, 0);
    assert(distances[0] == 0);
    assert(distances[1] == 1);
    assert(distances[2] == 2);
}

void testCycleGraph() {
    const std::string_view input = R"(
4
4
0 1
1 2
2 3
3 0
0
)";
    auto distances = runGraphTest(input, 0);
    assert(distances[0] == 0);
    assert(distances[1] == 1);
    assert(distances[2] == 2);
    assert(distances[3] == 1);
}

void testMultipleEdges() {
    const std::string_view input = R"(
3
4
0 1
0 1
1 2
1 2
0
)";
    auto distances = runGraphTest(input, 0);
    assert(distances[0] == 0);
    assert(distances[1] == 1);
    assert(distances[2] == 2);
}

void testStarGraph() {
    const std::string_view input = R"(
5
4
0 1
0 2
0 3
0 4
0
)";
    auto distances = runGraphTest(input, 0);
    assert(distances[0] == 0);
    assert(distances[1] == 1);
    assert(distances[2] == 1);
    assert(distances[3] == 1);
    assert(distances[4] == 1);
}

void testLargeChainGraph() {
    const int n = 1000;
    std::ostringstream oss;
    oss << n << "\n" << n - 1 << "\n";
    for (int i = 0; i < n - 1; i++) {
        oss << i << " " << i + 1 << "\n";
    }
    oss << "0\n";
    auto distances = runGraphTest(oss.str(), 0);
    for (int i : std::views::iota(0, n)) {
        assert(distances[i] == i);
    }
}

void testTwoComponents() {
    const std::string_view input = R"(
6
3
0 1
1 2
0 2
0
)";
    auto distances = runGraphTest(input, 0);
    assert(distances[0] == 0);
    assert(distances[1] == 1);
    assert(distances[2] == 1);
    assert(distances[3] == -1);
    assert(distances[4] == -1);
    assert(distances[5] == -1);
}

void testEmptyEdges() {
    const std::string_view input = R"(
4
0
2
)";
    auto distances = runGraphTest(input, 2);
    assert(distances[0] == -1);
    assert(distances[1] == -1);
    assert(distances[2] == 0);
    assert(distances[3] == -1);
}

void run_test(
    const std::string& test_name, const std::function<void()>& test_func,
    const std::source_location& loc = std::source_location::current()) {
    try {
        test_func();
        std::print("[PASS] {}\n", test_name);
    } catch (const std::exception& e) {
        std::print(stderr, "[FAIL] {} at {}:{} - {}\n", test_name,
                   loc.file_name(), loc.line(), e.what());
        std::exit(1);
    }
}

int main() {
    const std::vector<std::pair<std::string, std::function<void()>>> tests{
        {"testValidGraph", testValidGraph},
        {"testInvalidInput", testInvalidInput},
        {"testOutOfRangeStart", testOutOfRangeStart},
        {"testSingleVertex", testSingleVertex},
        {"testDisconnectedGraph", testDisconnectedGraph},
        {"testCompleteGraph", testCompleteGraph},
        {"testSelfLoop", testSelfLoop},
        {"testCycleGraph", testCycleGraph},
        {"testMultipleEdges", testMultipleEdges},
        {"testStarGraph", testStarGraph},
        {"testLargeChainGraph", testLargeChainGraph},
        {"testTwoComponents", testTwoComponents},
        {"testEmptyEdges", testEmptyEdges}};

    for (const auto& [name, func] : tests) {
        run_test(name, func);
    }
    std::cout << "All tests passed.\n";
    return 0;
}