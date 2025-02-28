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

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <iostream>
#include <memory>

// Memory benchmarking global class
class MemoryBenchmarking {
private:
  size_t totalMemoryAllocated; // Total bytes of allocated memory

  /// @brief Class default constructor
  explicit MemoryBenchmarking() = default;

  MemoryBenchmarking(MemoryBenchmarking const &) = delete;
  MemoryBenchmarking &operator=(MemoryBenchmarking const &) = delete;

  /// @brief Class default destructor
  ~MemoryBenchmarking() = default;

public:
  /// @brief Getter of instance of memory benchmarking class
  /// @return static link to the instance of this class
  static MemoryBenchmarking &getInstance() {
    static MemoryBenchmarking memoryBenchmarkingInstance;

    return memoryBenchmarkingInstance;
  }

  /// @brief Getter of the total number of allocated bytes value
  /// @return total number of allocated bytes value
  size_t getTotalMemoryAllocated() const noexcept {
    return totalMemoryAllocated;
  }

  // Friends methods of this class
  friend void *operator new(size_t size);
  friend void operator delete(void *ptr) noexcept;
};

// Redefinition of the allocating memory method
void *operator new(size_t size);

// Redefinition of the deleting memory method
void operator delete(void *ptr) noexcept;

#endif // MEMORY_HPP