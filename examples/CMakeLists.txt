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

cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER_LAUNCHER ${CMAKE_COMMAND} -E env ASAN_OPTIONS=detect_odr_violation=0 ${CMAKE_CXX_COMPILER_LAUNCHER})

set(ALGO_ANALYSIS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
include(${ALGO_ANALYSIS_DIR}/cpp/cmake/set_ifndef.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_VERBOSE_MAKEFILE 1)

set(PROJECT_NAME algo_analysis_examples)
project(${PROJECT_NAME})

set_ifndef(ALGO_ANALYSIS_INCLUDE_DIR ${ALGO_ANALYSIS_DIR}/cpp/include)
include_directories(SYSTEM ${ALGO_ANALYSIS_INCLUDE_DIR})

add_executable(ford_bellman_example "${ALGO_ANALYSIS_DIR}/cpp/algo_analysis/memory/memory.cpp" "dfs.cpp")
