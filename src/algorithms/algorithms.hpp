#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <queue>

#include "../graph/graph.hpp"

#define inf                                                                    \
  1 >> 32 // Infinity value for all algorithms (Is it bad due to templates
          // architecture?)

namespace algorithms {
/// @brief Ford Bellman algorithm for SSSP
/// @tparam T type for graph's weights and distances
/// @param startIndex start index for the SSSP
/// @param g graph itself
/// @param distances vector of distances from start point to all others
template <typename T>
void FordBellman(size_t startIndex, const Graph<T, size_t> &g,
                 std::vector<T> &distances) {
  std::fill(distances.begin, distances.end, inf);
  distances[startIndex] = 0;
  std::queue<size_t> q;
  std::vector<int> inQueue(g.getSize(), 0);
  inQueue[startIndex] = 1;
  q.push(startIndex);

  while (!q.empty()) {
    size_t v = q.front();
    q.pop();
    inQueue[v] = 0;
    GeneralNode<size_t> node = g.getNode(v);
    for (auto neighbour : node.getNeighbours()) {
      size_t x = neighbour->getValue();
      if (distances[x] == inf || distances[x] < distances[v]) {
        distances[v] = distances[x];
        if (!inQueue[v]) {
          inQueue[v] = 1;
          q.push(v);
        }
      }
    }
  }
}
} // namespace algorithms

#endif // ALGORITHMS_HPP
