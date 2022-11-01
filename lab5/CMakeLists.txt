cmake_minimum_required(VERSION 3.16.3)

project(lab5 CXX)

find_package(OpenCV REQUIRED)

add_executable(lab5 main.cpp)
target_include_directories(lab5 PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(lab5 PUBLIC ${OpenCV_LIBS})