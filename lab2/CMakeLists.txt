cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME lab2)
set(SOURCE_DIR src)
set(SOURCE ${SOURCE_DIR}/main.cpp)
set(LIBRARY_DIR lib)
set(LIBRARY monte_carlo point random)

if(O0)
    message(STATUS "Flags -O0 included")
    set(CMAKE_CXX_FLAGS "-O0")
endif()

if(O1)
    message(STATUS "Flags -O1 included")
    set(CMAKE_CXX_FLAGS "-O1")
endif()

if(O2)
    message(STATUS "Flags -O2 included")
    set(CMAKE_CXX_FLAGS "-O2")
endif()

if(O3)
    message(STATUS "Flags -O3 included")
    set(CMAKE_CXX_FLAGS "-O3")
endif()

if(Os)
    message(STATUS "Flags -Os included")
    set(CMAKE_CXX_FLAGS "-Os")
endif()

if(Ofast)
    message(STATUS "Flags -Ofast included")
    set(CMAKE_CXX_FLAGS "-Ofast")
endif()

if(Og)
    message(STATUS "Flags -Og included")
    set(CMAKE_CXX_FLAGS "-Og")
endif()

project(${PROJECT_NAME} CXX)

add_executable(${PROJECT_NAME} ${SOURCE})

foreach(LIBRARY ${LIBRARY})
    add_subdirectory("${LIBRARY_DIR}/${LIBRARY}")
endforeach(LIBRARY)

find_library(LIBRT rt)
if(LIBRT)
    message(STATUS "Library rt installed")
    string(APPEND LIBRARY ";${LIBRT}")
else()
    message(STATUS "Library rt skipped")
endif()

target_link_libraries(${PROJECT_NAME} ${LIBRARY})