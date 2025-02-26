/*
 * Copyright (c) 2022-2025, HSE CORPORATION.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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