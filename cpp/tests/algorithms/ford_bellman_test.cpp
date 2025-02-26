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

#include "../tests.hpp"

// Demonstrate some basic assertions.
TEST(FordBellman, Graph1) {
  std::unique_ptr<Graph> graph_1 =
      std::make_unique<Graph>("../tests/.data/graph_example_1.txt");

  FunctionType<int, int>::Type f = algorithms::FordBellman<int, int>;

  std::vector<Graph *> graphs;

  graphs.push_back(graph_1.get());
  SSSP<int, int> task(graphs, {0}, f);

  task.run();

  std::vector<std::vector<int>> right_distances = {{0, 10, 30, 40}};

  for (int i = 0; i < task.getDistances().size(); i++) {
    for (int j = 0; j < task.getDistances()[i].size(); j++) {
      EXPECT_EQ(task.getDistances()[i][j], right_distances[i][j]);
    }
  }
}
