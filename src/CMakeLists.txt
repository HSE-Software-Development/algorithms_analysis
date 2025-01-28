cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME HSE_SD)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

# include_directories(include)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.hpp")

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

add_executable(${PROJECT_NAME} ${SOURCES})
