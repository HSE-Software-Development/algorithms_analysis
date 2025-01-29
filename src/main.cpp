#include <iostream>

#include "tasks/tasks.hpp"

template <typename T, typename K> struct FunctionType {
    typedef std::function<void(size_t, GeneralGraph<T, K> *, std::vector<T> &)> Type;
};

int main() {
    FunctionType<int, int>::Type f = algorithms::FordBellman<int, int>;

    std::unique_ptr<Graph> graph_1 = std::make_unique<Graph>("../.cache/graph_example_1.txt");
    std::unique_ptr<Graph> graph_2 = std::make_unique<Graph>("../.cache/graph_example_2.txt");
    std::unique_ptr<Graph> graph_3 = std::make_unique<Graph>("../.cache/graph_example_3.txt");

    std::vector<Graph *> graphs;
    graphs.push_back(graph_1.get());
    graphs.push_back(graph_2.get());
    graphs.push_back(graph_3.get());

    SSSP<int, int> task(graphs, {0, 1, 3}, f);

    task.run();

    return 0;
}