cmake_minimum_required(VERSION 3.5.1)
project(lab1 CXX)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

add_executable(lab1 main.cpp)

target_include_directories(lab1 PUBLIC monte_carlo)

add_subdirectory(monte_carlo)

target_link_libraries(lab1 PUBLIC monte_carlo)