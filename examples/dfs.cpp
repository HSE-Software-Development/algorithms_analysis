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

#include <algo_analysis/task.hpp>
#include <algo_analysis/algorithms/dfs.hpp>
#include <iostream>

int main() {
  Task<int> task(
      "../tests/.data/task_01.txt"
  );

  DFSAlgorithm<int> algo;
  Task<int>::Statistics stats = task.estimate(algo);

  std::cout << "MU: " << stats.initializationMemoryUsage << "\n";
  std::cout << "IT: " << stats.initializationTime << "\n";
  return 0;
}