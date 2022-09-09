add_library(point STATIC point.cpp)

target_include_directories(point PUBLIC random)

add_subdirectory(random)

target_link_libraries(point PUBLIC random)