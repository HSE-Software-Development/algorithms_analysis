#include <iostream>

#include "tasks/tasks.hpp"

template<typename T> struct FunctionType
{
    typedef std::function<void(size_t, GeneralGraph<T, size_t> *, std::vector<T> &)> Type;
};

int main() {
    /*GeneralNode<int> a(1);
    auto x = a.getNeighbours();
    GeneralGraph<size_t, size_t> g;
    auto v = std::vector<size_t>();
    //   algorithms::FordBellman<size_t>((size_t)0, g, v);
    std::cout << "abc" << std::endl;

    return 0;*/

    Graph graph("../../.cache/graph_example.txt");


    std::cout << "asdfasdf";
    FunctionType<int>::Type f = algorithms::FordBellman<int>;
    SSSP<int, size_t> task({"../../.cache/graph_example.txt"}, {0}, f);
    task.run(1);
    return 0;
}