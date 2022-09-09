cmake_minimum_required(VERSION 3.5.1)
project(lab1 CXX)

add_executable(lab1 main.cpp)

target_include_directories(lab1 PUBLIC monte_carlo)

add_subdirectory(monte_carlo)

target_link_libraries(lab1 PUBLIC monte_carlo)

if(USE_CLOCK_GETTIME)
    message(STATUS "Macro USE_CLOCK_GETTIME installed")
    target_compile_definitions (lab1 PUBLIC USE_CLOCK_GETTIME)
endif()

if(USE_TIMES)
    message(STATUS "Macro USE_TIMES installed")
    target_compile_definitions (lab1 PUBLIC USE_TIMES)
endif()

if(USE_RDTSC)
    message(STATUS "Macro USE_RDTSC installed")
    target_compile_definitions (lab1 PUBLIC USE_RDTSC)
endif()