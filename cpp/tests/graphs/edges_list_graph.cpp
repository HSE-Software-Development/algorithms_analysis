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
#include <sstream>


TEST(EdgesListGraph1, Serialization) {
    EdgesListGraph<int> graph({
        Edge<int>{0, 1, 10},
        Edge<int>{0, 2, 10},
        Edge<int>{1, 3, 10},
    });

    std::stringstream ss;
    graph.serialize(ss);

    EXPECT_EQ(ss.str(), std::string("3\n0 --> 1 w: 10\n"
"0 --> 2 w: 10\n"
"1 --> 3 w: 10\n"));

}

TEST(EdgesListGraph1, Deserialization) {

    EdgesListGraph<int> graph;

    std::stringstream ss;
    ss << std::string("3\n0 --> 1 w: 10\n"
"0 --> 2 w: 10\n"
"1 --> 3 w: 10\n");

    graph.deserialize(ss);

    std::vector<std::vector<int>> expectedGraph = {
        {0, 1, 10},
        {0, 2, 10},
        {1, 3, 10}
    };

    for (size_t i = 0; i < graph.edges.size(); i++) {
        EXPECT_EQ(graph.edges[i].fromIndex, expectedGraph[i][0]); 
        EXPECT_EQ(graph.edges[i].toIndex, expectedGraph[i][1]); 
        EXPECT_EQ(graph.edges[i].weight, expectedGraph[i][2]); 
    }
}