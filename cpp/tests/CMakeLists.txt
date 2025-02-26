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

# GoogleTest Preparation - Code block copied from
# https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY
    https://github.com/google/googletest.git
  GIT_TAG v1.15.2)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set_ifndef(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES "algorithms/*.cpp" "graphs/*.cpp")

add_executable(${PROJECT_NAME}_tests ${PROJECT_SOURCES} ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME}_tests gtest gtest_main)
