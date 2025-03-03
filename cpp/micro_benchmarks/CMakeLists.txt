# Copyright (c) 2022-2025, HSE CORPORATION.  All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Google Benchmark Preparation - Same as google test ../tests/CMakeLists.txt
# Google Benchmark is provided under Apache-2.0 license
include(FetchContent)
set(BENCHMARK_ENABLE_TESTING
    OFF
    CACHE INTERNAL "Disable google-benchmark tests")
set(BENCHMARK_ENABLE_INSTALL
    OFF
    CACHE INTERNAL "Disable google-benchmark install")
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.8.3)
FetchContent_MakeAvailable(googlebenchmark)

include(../cmake/boost.cmake)

add_custom_target(micro_benchmarks)

include_directories(SYSTEM ${ALGO_ANALYSIS_INCLUDE_DIR})

set(TOP_LEVEL_DIR "${PROJECT_SOURCE_DIR}/..")

function(add_benchmark test_name test_src)
  add_executable(${test_name} ${PROJECT_SOURCES} ${test_src})

  target_link_libraries(${test_name} PUBLIC benchmark::benchmark Boost::heap)

  target_compile_features(${test_name} PRIVATE cxx_std_17)
  target_compile_definitions(${test_name} PUBLIC TOP_LEVEL_DIR="${TOP_LEVEL_DIR}")

  add_dependencies(micro_benchmarks ${test_name})
endfunction()

add_benchmark(DFSBenchmark dfs.cpp)
add_benchmark(BFSBenchmark bfs.cpp)
add_benchmark(DijkstraBenchmark dijkstra.cpp)
add_benchmark(DijkstraWithFibBenchmark dijkstra_with_fib.cpp)
add_benchmark(FordBellmanBenchmark ford_bellman.cpp)
add_benchmark(FloidBenchmark floid.cpp)
