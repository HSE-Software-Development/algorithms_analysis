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

#ifndef TASK_HPP
#define TASK_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <functional>

#include <algo_analysis/algorithms/algorithm.hpp>
#include <algo_analysis/graphs/edges_list_graph.hpp>
#include <algo_analysis/memory/memory.hpp>

template<typename WeightType>
struct Task{

    uint64_t getTimeInMs() noexcept {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
            .count();
    }

    EdgesListGraph<WeightType> graph;
    std::vector<size_t> startIndexes;


    struct Statistics {
        size_t initializationMemoryUsage;
        std::vector<size_t> computationMemoryUsage;
        uint64_t initializationTime;
        std::vector<uint64_t> computationTime;
    };


    Task(const std::string &filePath) {
        fromFile(filePath);
    }

    Task(const std::vector<size_t> &startIndexes_, const EdgesListGraph<WeightType> &graph_) : graph(graph_), startIndexes(startIndexes_) {
    }


    void serialize(std::ostream &stream) {
        graph.serialize(stream);

        stream << startIndexes.size() << '\n';
        for (int i = 0; i < startIndexes.size(); i++) {
            stream << startIndexes[i] << '\n';
        }
    } 

    void deserialize(std::istream &stream) {
        graph.deserialize(stream);

        size_t numberOfStartIndexes;
        stream >> numberOfStartIndexes;
        startIndexes = std::vector<size_t>(numberOfStartIndexes);

        for (int i = 0; i < numberOfStartIndexes; i++) {
            stream >> startIndexes[i];
        }
    }

    void toFile(std::string &filePath) {
        std::ofstream file(filePath);
        serialize(file);
    }

    void fromFile(const std::string &filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Ошибка: Не удалось открыть файл " << filePath << std::endl;
            return;
        }
        deserialize(file);
    }

    std::vector<std::vector<WeightType>> run(Algorithm<WeightType> &algorithm) {
        std::vector<std::vector<WeightType>> result;
        algorithm.fit(graph);
        for (size_t startIndex : startIndexes) {
            result.push_back(algorithm.computeDistances(startIndex));
        }
        return result;
    }

    Statistics estimate(Algorithm<WeightType> &algorithm) {
        Statistics stats;

        double initializationStartMemory = MemoryBenchmarking::getInstance().getTotalMemoryAllocated();
        double initializationStartTime = static_cast<double>(getTimeInMs());
        algorithm.fit(graph);
        stats.initializationTime = static_cast<double>(getTimeInMs()) - initializationStartTime;
        stats.initializationMemoryUsage = static_cast<double>(
            MemoryBenchmarking::getInstance().getTotalMemoryAllocated() - initializationStartMemory
        ) / 1000;

        for (size_t startIndex : startIndexes) {
            double computationStartMemory = MemoryBenchmarking::getInstance().getTotalMemoryAllocated();
            double computationStartTime = static_cast<double>(getTimeInMs());

            auto res = algorithm.computeDistances(startIndex);

            stats.computationTime.push_back(
                static_cast<double>(getTimeInMs()) - computationStartTime
            );
            stats.computationMemoryUsage.push_back(
                static_cast<double>(
                    MemoryBenchmarking::getInstance().getTotalMemoryAllocated() - computationStartMemory
                ) / 1000
            );

            // for (WeightType dist : res) {
            //     std::cout << "\t" << dist;
            // }
        }
        return stats;
    }

}; 




#endif // GRAPH_HPP
