#include <iostream>

#include "tasks/tasks.hpp"

int main() {
  GeneralNode<int> a(1);
  auto x = a.getNeighbours();
  Graph<size_t, size_t> g;
  auto v = std::vector<size_t>();
//   algorithms::FordBellman<size_t>((size_t)0, g, v);
  std::cout << "abc" << std::endl;

  return 0;
}