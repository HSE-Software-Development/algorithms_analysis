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

include(CheckLanguage)
include(cmake/set_ifndef.cmake)

set_ifndef(PROJECT_NAME algo_analysis)
project(${PROJECT_NAME} LANGUAGES CXX)

option(BUILD_TESTS "Build Google tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_MICRO_BENCHMARKS "Build C++ micro benchmarks" ON)
option(WARNING_IS_ERROR "Treat all warnings as errors" ON)

set_ifndef(ALGO_ANALYSIS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
set_ifndef(ALGO_ANALYSIS_INCLUDE_DIR ${ALGO_ANALYSIS_DIR}/cpp/include)

if(BUILD_TESTS)
  message(STATUS "Building Google tests")
else()
  message(STATUS "Not building Google tests")
endif()

if(BUILD_EXAMPLES)
  message(STATUS "Building examples")
else()
  message(STATUS "Not building examples")
endif()

if(BUILD_MICRO_BENCHMARKS)
  message(STATUS "Building C++ micro benchmarks")
else()
  message(STATUS "Not building C++ micro benchmarks")
endif()

if(WARNING_IS_ERROR)
  message(STATUS "All warnings will be treat as errors")
endif()

file(GLOB PROJECT_SOURCES ${PROJECT_NAME}/memory/*.cpp)

if(WARNING_IS_ERROR)
  set(CMAKE_COMPILE_WARNING_AS_ERROR ON)    
endif()

# For detecting memory leaks
add_compile_options(-fsanitize=address)
add_compile_options(-fsanitize=undefined)
add_link_options(-fsanitize=address)
add_link_options(-fsanitize=undefined)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(BUILD_MICRO_BENCHMARKS)
  add_subdirectory(micro_benchmarks)
endif()

option(MEASURE_BUILD_TIME "Measure the build time of each module" ON)
if(MEASURE_BUILD_TIME)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_CUSTOM "${CMAKE_COMMAND} -E time")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")
endif()