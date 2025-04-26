cmake_minimum_required(VERSION 3.31)
project(Benchmarking C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -O0)

add_executable(Benchmarking main.c)
