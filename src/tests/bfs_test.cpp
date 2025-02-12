#include "../tasks/tasks.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

template <typename T, typename K> struct FunctionType {
    typedef std::function<void(size_t, GeneralGraph<T, K> *, std::vector<T> &)> Type;
};

// Demonstrate some basic assertions.
TEST(BFS, Graph1) {
    std::unique_ptr<Graph> graph_1 = std::make_unique<Graph>("../../.cache/graph_example_4.txt");

    std::cout << graph_1.get()->getSize() << std::endl;

    FunctionType<int, int>::Type f = algorithms::BFS<int, int>;

    std::vector<Graph *> graphs;

    graphs.push_back(graph_1.get());
    SSSP<int, int> task(graphs, {0}, f);

    task.run();

    std::vector<std::vector<int>> right_distances = {{0, 10, 20, 40, 80}};

    std::cout << task.getDistances().size() << std::endl;
    for (int i = 0; i < task.getDistances().size(); i++) {
        for (int j = 0; j < task.getDistances()[i].size(); j++) {
            EXPECT_EQ(task.getDistances()[i][j], right_distances[i][j]);
        }
    }
}


