cmake_minimum_required(VERSION 3.21)
project(aoc23 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(executables d1)

foreach(executable ${executables})
    add_executable(${executable} "${executable}/main.cxx")
endforeach()

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    -checks=*;
    -header-filter=.*;
)