cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(lab1 CXX)

add_executable(lab1 main.cpp)

if(SYS_TIME)
    message(STATUS "Macro SYS_TIME installed")
    target_compile_definitions (lab1 PUBLIC SYS_TIME)

    find_library(LIBRT rt)
    if(LIBRT)
        message(STATUS "Library rt installed")
        target_link_libraries(lab1 ${LIBRT})
    else()
        message(STATUS "Library rt skipped")
    endif()
endif()

if(PROC_TIME)
    message(STATUS "Macro PROC_TIME installed")
    target_compile_definitions (lab1 PUBLIC PROC_TIME)
endif()

if(CPU_TIME_STAMP_COUNTER)
    message(STATUS "Macro CPU_TIME_STAMP_COUNTER installed")
    target_compile_definitions (lab1 PUBLIC CPU_TIME_STAMP_COUNTER)
endif()