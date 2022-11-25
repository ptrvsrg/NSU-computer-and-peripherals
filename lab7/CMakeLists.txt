cmake_minimum_required(VERSION 3.16.3)

project(lab7)

enable_testing()
add_executable(default
        src/default.cpp)
add_test(test_default default)

add_executable(manual
        src/manual.cpp)
target_compile_options(manual PUBLIC
        -msse
        -msse2
        -msse3
        -msse4)
add_test(test_manual manual)

find_package(MKL CONFIG)
if (${MKL_FOUND})
    message(STATUS "MKL found")
    add_executable(BLAS
            src/BLAS.cpp)
    target_compile_options(BLAS PUBLIC
            $<TARGET_PROPERTY:MKL::MKL,INTERFACE_COMPILE_OPTIONS>)
    target_include_directories(BLAS PUBLIC
            $<TARGET_PROPERTY:MKL::MKL,INTERFACE_INCLUDE_DIRECTORIES>)
    target_link_libraries(BLAS PUBLIC
            $<LINK_ONLY:MKL::MKL>)
    add_test(test_BLAS BLAS)
endif()
