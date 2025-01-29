#include <gtest/gtest.h>
#include "../tasks/tasks.hpp"

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
    EXPECT_EQ(7 * 6, 42);
}
