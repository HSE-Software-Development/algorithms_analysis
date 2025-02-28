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
#include <algo_analysis/algorithms/bfs_with_zeroes.hpp>
#include <algo_analysis/task.hpp>
#include <algo_analysis/graphs/edges_list_graph.hpp>
#include <algo_analysis/graphs/edge.hpp>


// Demonstrate some basic assertions.
TEST(BFSWithZeroes, Task01) {

    Task<int> task(
        "../tests/.data/task_01.txt"
    );
    BFSWithZerosAlgorithm<int> bfs;
    auto results = task.run(bfs);
    std::vector<std::vector<int>> expectedResult = {
        {0, 10, 10, 20},
    };

    EXPECT_EQ(results, expectedResult);
}


TEST(BFSWithZeroes, TaskFullGraph) {

    Task<int> task(
        "../tests/.data/task_full_graph_ones_and_zeroes.txt"
    );
    BFSWithZerosAlgorithm<int> algo;
    auto results = task.run(algo);
    std::vector<std::vector<int>> expectedResult = {
        { { 0, 1, 1, 1 }, { 0, 0, 1, 1 } }
    };

    EXPECT_EQ(results, expectedResult);
}