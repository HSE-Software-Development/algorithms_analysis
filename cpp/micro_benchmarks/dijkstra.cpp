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

#include <benchmark/benchmark.h>
#include <algo_analysis/algorithms/dijkstra.hpp>
#include <algo_analysis/task.hpp>
#include <algo_analysis/graphs/edges_list_graph.hpp>
#include <algo_analysis/graphs/edge.hpp>
#include <iostream>

void pointQuery(int maxCapacity) {
    Task<int> task(
        "../tests/.data/task_01.txt"
    );

    DijkstraAlgorithm<int> dijkstra;

    task.run(dijkstra);
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
