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
#include <benchmark/benchmark.h>
#include <iostream>

void pointQuery(int maxCapacity) {
  std::unique_ptr<Graph> graph_1 =
      std::make_unique<Graph>("../micro_benchmarks/.data/graph_example_1.txt");
  std::unique_ptr<Graph> graph_2 =
      std::make_unique<Graph>("../micro_benchmarks/.data/graph_example_2.txt");
  std::unique_ptr<Graph> graph_3 =
      std::make_unique<Graph>("../micro_benchmarks/.data/graph_example_3.txt");
  std::unique_ptr<Graph> graph_4 =
      std::make_unique<Graph>("../micro_benchmarks/.data/graph_example_4.txt");
  std::unique_ptr<Graph> graph_5 =
      std::make_unique<Graph>("../micro_benchmarks/.data/graph_example_10.txt");

  SSSP<int, int>::AlgorithmType algorithm = algorithms::DFS<int, int>;

  std::vector<size_t> startNodesIndexes(5, 0);
  std::vector<Graph *> graphs;
  graphs.push_back(graph_1.get());
  graphs.push_back(graph_2.get());
  graphs.push_back(graph_3.get());
  graphs.push_back(graph_4.get());
  graphs.push_back(graph_5.get());

  SSSP<int, int> task(graphs, startNodesIndexes, algorithm);

  task.run();
}

void benchMark(benchmark::State &state) {
  int maxCapacity = state.range(0);
  for (auto _ : state) {
    pointQuery(maxCapacity);
  }
}

int main(int argc, char **argv) {
  BENCHMARK(benchMark)->DenseRange(1, 5);

  ::benchmark::Initialize(&argc, argv);
  if (::benchmark::ReportUnrecognizedArguments(argc, argv)) {
    return 1;
  }
  ::benchmark::RunSpecifiedBenchmarks();

  return 0;
}
