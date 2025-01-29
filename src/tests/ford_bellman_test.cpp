#include <gtest/gtest.h>
#include "../tasks/tasks.hpp"
#include <vector>
#include <iostream>


template <typename T, typename K> struct FunctionType {
    typedef std::function<void(size_t, GeneralGraph<T, K> *, std::vector<T> &)> Type;
};

// Demonstrate some basic assertions.
TEST(FordBellman, Graph1) {
    std::unique_ptr<Graph> graph_1 = std::make_unique<Graph>("../.cache/graph_example.txt");
    FunctionType<int, int>::Type f = algorithms::FordBellman<int, int>;

    std::vector<Graph *> graphs;

    graphs.push_back(graph_1.get());
    SSSP<int, int> task(graphs, {0}, f);

    task.run();

    std::vector<std::vector<int>> right_distances = {
        {0, 10, 30, 40}
    };

    for (int i = 0; i < task.distances.size(); i++) {
        for (int j = 0; j < task.distances[i].size(); j++) {
            EXPECT_EQ(task.distances[i][j], right_distances[i][j]);
        }
    }
}
