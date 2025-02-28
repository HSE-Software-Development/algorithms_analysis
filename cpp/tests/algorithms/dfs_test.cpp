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
#include <algo_analysis/algorithms/dfs.hpp>
#include <algo_analysis/task.hpp>
#include <algo_analysis/graphs/edges_list_graph.hpp>
#include <algo_analysis/graphs/edge.hpp>


TEST(DFS, Task01) {

    Task<int> task(
        "../tests/.data/task_01.txt"
    );
    DFSAlgorithm<int> dfs;
    auto results = task.run(dfs);
    std::vector<std::vector<int>> expectedResult = {
        {0, 10, 10, 20},
    };

    EXPECT_EQ(results, expectedResult);
}

TEST(DFS, TaskTree) {

    Task<int> task(
        "../tests/.data/task_tree.txt"
    );
    DFSAlgorithm<int> dfs;
    auto results = task.run(dfs);
    std::vector<std::vector<int>> expectedResult = {
        { 0, 5, 3, 13, 7, 10, 7 }
    };

    EXPECT_EQ(results, expectedResult);
}


TEST(DFS, TaskFullGraph) {

    Task<int> task(
        "../tests/.data/task_full_graph.txt"
    );
    DFSAlgorithm<int> dfs;
    auto results = task.run(dfs);
    std::vector<std::vector<int>> expectedResult = {
        { 0, 7, 10, 14 }, { -1, 0, 3, 7 }
    };

    EXPECT_EQ(results, expectedResult);
}


TEST(DFS, TaskSeveralComponents) {

    Task<int> task(
        "../tests/.data/task_several_components.txt"
    );
    DFSAlgorithm<int> dfs;
    auto results = task.run(dfs);
    std::vector<std::vector<int>> expectedResult = {
        { 0, 2, 7, 4, 7, 10, 16, -1, -1, -1 }, { -1, -1, -1, -1, 0, 3, 9, -1, -1, -1 }
    };

    EXPECT_EQ(results, expectedResult);
}

TEST(DFS, TaskCycleWithExtraEdges) {

    Task<int> task(
        "../tests/.data/task_cycle_with_extra_edges.txt"
    );
    DFSAlgorithm<int> dfs;
    auto results = task.run(dfs);
    std::vector<std::vector<int>> expectedResult = {
        { 0, 6, 7, 11, 14, 16 }, { 15, 0, 1, 5, 8, 10 }
    };

    EXPECT_EQ(results, expectedResult);
}