#include <algo_analysis/task/task.hpp>
#include <iostream>

template <typename T, typename K> struct Algorithm {
  typedef std::function<void(size_t, GeneralGraph<T, K> *, std::vector<T> &)>
      Type;
};

int main() {
  std::unique_ptr<Graph> graph_1 =
      std::make_unique<Graph>("../.data/graph_example_10.txt");
  Algorithm<int, int>::Type f = algorithms::FordBellman<int, int>;

  std::vector<Graph *> graphs;

  graphs.push_back(graph_1.get());
  SSSP<int, int> task(graphs, {0}, f);

  task.run();

  return 0;
}