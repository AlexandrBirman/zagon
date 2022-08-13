cmake_minimum_required(VERSION 3.21)
project(maniso)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(maniso
        src/container.cpp)
