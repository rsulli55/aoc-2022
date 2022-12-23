cmake_minimum_required(VERSION 3.20)
project(aoc-2022)

include(FetchContent)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
message(STATUS "install prefix = " ${CMAKE_INSTALL_PREFIX})

FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0
)
FetchContent_MakeAvailable(fmt)

add_subdirectory(src)
