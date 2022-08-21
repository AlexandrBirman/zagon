cmake_minimum_required(VERSION 3.21.0)
project(zagon VERSION 0.1.0 LANGUAGES CXX)

option(ZAGON_TESTING "Unit tests enabled" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

set(SRCS src/main.cpp src/hello.h)
add_executable(zagon ${SRCS})

if(NOT ZAGON_TESTING)
    message(STATUS "Unit tests disabled")
else() 
    add_subdirectory(test)
endif()
