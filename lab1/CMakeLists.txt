cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME lab1)
set(SOURCE_DIR src)
set(SOURCE ${SOURCE_DIR}/main.cpp)
set(LIBRARY_DIR lib)
set(LIBRARY monte_carlo point random)

project(${PROJECT_NAME} CXX)

add_executable(${PROJECT_NAME} ${SOURCE})

foreach(LIBRARY ${LIBRARY})
    add_subdirectory("${LIBRARY_DIR}/${LIBRARY}")
endforeach(LIBRARY)

if(SYS_TIME)
    message(STATUS "Macro SYS_TIME installed")
    target_compile_definitions (lab1 PUBLIC SYS_TIME)

    find_library(LIBRT rt)
    if(LIBRT)
        message(STATUS "Library rt installed")
        string(APPEND LIBRARY ";${LIBRT}")
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

target_link_libraries(${PROJECT_NAME} ${LIBRARY})