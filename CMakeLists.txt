cmake_minimum_required(VERSION 3.15)
project(gameoflife)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)