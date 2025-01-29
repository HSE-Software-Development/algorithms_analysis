cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME HSE_SD)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

# include_directories(include)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.hpp")
file(GLOB TEST_SOURCES "tests/*.cpp")

if (APPLE)
    message(STATUS ">>> Apple detected")
elseif (MSVC OR MSYS OR MINGW)
    message(STATUS ">>> Windows detected")
elseif (UNIX AND NOT APPLE)
    message(STATUS ">>> Linux detected")
else ()
    message(FATAL_ERROR "Not supported OS (only MacOS/Linux/Windows)")
endif ()


# for detecting memory leaks
add_compile_options(-fsanitize=address)
add_compile_options(-fsanitize=undefined)
add_link_options(-fsanitize=address)
add_link_options(-fsanitize=undefined)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(${PROJECT_NAME} ${SOURCES})

add_executable(AlgorithmTests ${TEST_SOURCES})

target_link_libraries(AlgorithmTests gtest gtest_main)