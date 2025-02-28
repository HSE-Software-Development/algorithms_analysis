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

#include <gtest/gtest.h>
#include <algo_analysis/algorithms/dijkstra.hpp>
#include <algo_analysis/task.hpp>
#include <algo_analysis/graphs/edges_list_graph.hpp>
#include <algo_analysis/graphs/edge.hpp>


TEST(Dijkstra, Task01) {

    Task<int> task(
        "../tests/.data/task_01.txt"
    );
    DijkstraAlgorithm<int> dijkstra;
    auto results = task.run(dijkstra);
    std::vector<std::vector<int>> expectedResult = {
        {0, 10, 10, 20},
    };

    EXPECT_EQ(results, expectedResult);
}


TEST(Dijkstra, TaskTree) {

    Task<int> task(
        "../tests/.data/task_tree.txt"
    );
    DijkstraAlgorithm<int> algo;
    auto results = task.run(algo);
    std::vector<std::vector<int>> expectedResult = {
        { 0, 5, 3, 13, 7, 10, 7 }
    };

    EXPECT_EQ(results, expectedResult);
}

