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

#ifndef TASKS_HPP
#define TASKS_HPP

#include <functional>

#include <algo_analysis/algorithm/algorithm.hpp>
#include <algo_analysis/memory/memory.hpp>

// Task class
class Task {
public:
  /// @brief Run task method
  virtual void run(int logLevel) = 0;

  /// @brief Get current time in ms
  /// @return current time in ms
  uint64_t getTimeInMs() noexcept {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
        .count();
  }

  /// @brief Class destructor
  virtual ~Task() = default;

}; // End of class 'Task'

// SSSP task class
template <typename T, typename K> class SSSP : public Task {
public:
  typedef std::function<void(size_t, GeneralGraph<T, K> *, std::vector<T> &)>
      AlgorithmType;

private:
  std::vector<size_t> startNodeIndexes; // Start node index for the task
  std::vector<GeneralGraph<T, K> *>
      graphs;              // Non-owning pointer to the graphs for the task
  AlgorithmType algorithm; // Algorithm for the task
  std::vector<std::vector<T>>
      distances; // Distances from the start node to all others
  std::vector<double> timeBenchmarks; // Algorithm executions time in seconds
  double totalMemoryUsage;            // Total memory usage by whole task in KB
  std::vector<double> memoryBenchmarks; // Algorithm memory usage in KB

public:
  /// @brief Class constructor
  /// @param graphs_ vector of all graphs for the task
  /// @param startNodeIndexes_ vector of all start nodes for the task
  /// @param algorithm_ algorithm to complete the task
  SSSP(const std::vector<GeneralGraph<T, K> *> &graphs_,
       const std::vector<size_t> &startNodeIndexes_,
       const std::function<void(size_t, GeneralGraph<T, K> *, std::vector<T> &)>
           &algorithm_) {
    bool is_ok = !graphs_.empty() && !startNodeIndexes_.empty() &&
                 graphs_.size() == startNodeIndexes_.size();

    if (is_ok) {
      totalMemoryUsage =
          MemoryBenchmarking::getInstance().getTotalMemoryAllocated();
      const auto size = graphs_.size();

      startNodeIndexes = startNodeIndexes_;
      distances.resize(size);
      memoryBenchmarks.resize(size);
      timeBenchmarks.resize(size);
      graphs = graphs_;
      algorithm = algorithm_;
      totalMemoryUsage =
          static_cast<double>(
              MemoryBenchmarking::getInstance().getTotalMemoryAllocated() -
              totalMemoryUsage) /
          1000;
    } else {
      std::cout << "The number of graphs is 0 or is not equal to the number of "
                   "start nodes, aborting.."
                << std::endl;
    }
  }

  /// @brief Getter of SSSP start node's indexes
  /// @return All start node's indexes vector
  const std::vector<size_t> &getStartNodeIndexes() const noexcept {
    return startNodeIndexes;
  }

  /// @brief Getter of SSSP distances
  /// @return All distances vector
  const std::vector<std::vector<T>> &getDistances() const noexcept {
    return distances;
  }

  /// @brief Getter of SSSP memory usage
  /// @return All task's memory usage
  const double &getTaskMemoryBenchmark() const noexcept {
    return totalMemoryUsage;
  }

  /// @brief Getter of SSSP algorithm's memory usage
  /// @return All algorithm's memory benchmarks
  const std::vector<double> &getAlgorithmMemoryBenchmarks() const noexcept {
    return memoryBenchmarks;
  }

  /// @brief Getter of SSSP time benchmarks
  /// @return All time benchmarks
  const std::vector<double> &getTimeBenchmarks() const noexcept {
    return timeBenchmarks;
  }

  /// @brief Getter of SSSP graphs
  /// @return All graphs vector
  const std::vector<GeneralGraph<T, K> *> &getGraphs() const noexcept {
    return graphs;
  }

  /// @brief Executor of the task
  /// @param logLevel logging level
  void run(int logLevel = 1) override {
    const auto size = graphs.size();

    for (size_t i = 0; i < size; i++) {
      std::cout << "SSSP for graph #" << i + 1 << ":\n";
      if (graphs[i] == nullptr) {
        std::cout << "\tGraph pointer is nullptr, aborting..." << std::endl;
        continue;
      } else if (graphs[i]->getSize() == 0) {
        std::cout << "\tGraph is empty, skpping..." << std::endl;
        continue;
      }

      memoryBenchmarks[i] =
          MemoryBenchmarking::getInstance().getTotalMemoryAllocated();
      timeBenchmarks[i] = static_cast<double>(getTimeInMs());
      algorithm(startNodeIndexes[i], graphs[i], distances[i]);
      memoryBenchmarks[i] =
          static_cast<double>(
              MemoryBenchmarking::getInstance().getTotalMemoryAllocated() -
              memoryBenchmarks[i]) /
          1000;
      totalMemoryUsage += memoryBenchmarks[i];
      timeBenchmarks[i] =
          (static_cast<double>(getTimeInMs()) - timeBenchmarks[i]);
      // for (size_t j = 0; j < graphs[i]->getSize(); j++) {
      //     std::cout << "\t" << j + 1 << ") Distanse from node #" <<
      //     startNodeIndexes[i] << " to node #" << j
      //               << " = " << distances[i][j] << ";\n";
      // }
      std::cout << "\tMemory usage by task: " << totalMemoryUsage << " KB;\n";
      std::cout << "\tMemory usage by alorithm: " << memoryBenchmarks[i]
                << " KB;\n";
      std::cout << "\tTime: " << timeBenchmarks[i] << " ms." << std::endl;
    }
  }

  /// @brief Class destructor
  ~SSSP() = default;
}; // End of class 'SSSP'

// APSP task class
template <typename T, typename K> class APSP : public Task {
private:
  std::vector<GeneralGraph<T, K> *>
      graphs; // Non-owning pointer to the graphs for the task
  std::vector<std::vector<std::vector<T>>>
      distances; // Distances from any node to any others
  std::function<void(const GeneralGraph<T, K> *,
                     std::vector<std::vector<T>> &)>
      algorithm; // Algorithm for the task

public:
  /// @brief Class constructor
  /// @param graphs_ vector of all graphs for the task
  /// @param algorithm algorithm function instance
  APSP(const std::vector<GeneralGraph<T, K> *> &graphs_,
       std::function<void(const GeneralGraph<T, K> *,
                          std::vector<std::vector<T>> &)>
           algorithm_) {
    bool is_ok = !graphs_.empty();

    if (is_ok) {
      const auto size = graphs_.size();

      distances.resize(size);
      graphs = graphs_;
      algorithm = algorithm_;
    } else {
      std::cout << "The number of graphs is 0, aborting.." << std::endl;
    }
  }

  /// @brief Executor of the task
  void run(int logLevel = 1) override {}

  /// @brief Class destructor
  ~APSP() = default;
};

#endif // TASKS_HPP
