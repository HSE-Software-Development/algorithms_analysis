#include <iostream>

#include "tasks/tasks.hpp"

template <typename T, typename K> struct FunctionType {
    typedef std::function<void(size_t, GeneralGraph<T, K> *, std::vector<T> &)> Type;
};

int main() {
    std::unique_ptr<Graph> graph_1 = std::make_unique<Graph>("/home/dvlasov/projects/algorithms_analysis/.cache/graph_example_1.txt");
    FunctionType<int, int>::Type f = algorithms::FordBellman<int, int>;

    std::vector<Graph *> graphs;

    graphs.push_back(graph_1.get());
    SSSP<int, int> task(graphs, {0}, f);

    task.run();

    return 0;
}