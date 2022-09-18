cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(PROJECT_NAME lab3)
set(SOURCE_DIR src)
set(SOURCE ${SOURCE_DIR}/main.c)
set(LIBRARY_DIR lib)
set(LIBRARY monte_carlo point random)

project(${PROJECT_NAME} C)

add_executable(${PROJECT_NAME} ${SOURCE})

foreach(LIBRARY ${LIBRARY})
    add_subdirectory("${LIBRARY_DIR}/${LIBRARY}")
endforeach(LIBRARY)

target_link_libraries(${PROJECT_NAME} ${LIBRARY})