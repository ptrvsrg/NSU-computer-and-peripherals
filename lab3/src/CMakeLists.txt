cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_C_COMPILER "/usr/bin/gcc")

project(lab2 C)

add_executable(lab2 main.c)

add_subdirectory(monte_carlo)
target_include_directories(lab2 PUBLIC monte_carlo)
target_link_libraries(lab2 PUBLIC monte_carlo)