cmake_minimum_required(VERSION 3.16)
project(uBlas CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(gil_include_directories INTERFACE)
target_include_directories(gil_include_directories
        BEFORE
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_subdirectory(example)
