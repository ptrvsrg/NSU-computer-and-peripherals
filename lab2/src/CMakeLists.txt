cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(lab2 CXX)

add_executable(lab2 main.cpp)

add_subdirectory(monte_carlo)
target_include_directories(lab2 PUBLIC monte_carlo)
target_link_libraries(lab2 PUBLIC monte_carlo)

find_library(LIBRT rt)                                                                                                                                                                                                                                                                                        
if(LIBRT)
    message(STATUS "Library rt installed")
    target_link_libraries(lab2 PUBLIC ${LIBRT})
else()
    message(STATUS "Library rt skipped")
endif()

if(O0)
    message(STATUS "Flags -O0 included")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
endif()

if(O1)
    message(STATUS "Flags -O1 included")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
endif()

if(O2)
    message(STATUS "Flags -O2 included")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

if(O3)
    message(STATUS "Flags -O3 included")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

if(Os)
    message(STATUS "Flags -Os included")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
endif()

if(Ofast)
    message(STATUS "Flags -Ofast included")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
endif()

if(Og)
    message(STATUS "Flags -Og included")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og")
endif()