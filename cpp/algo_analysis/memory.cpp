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

#include <algo_analysis/memory/memory.hpp>

// Redefinition of the allocating memory method
void *operator new(size_t size) {
  MemoryBenchmarking::getInstance().totalMemoryAllocated += size;
  return ::std::malloc(size);
}

// Redefinition of the deleting memory method
void operator delete(void *ptr) noexcept { ::std::free(ptr); }
