add_library(monte_carlo STATIC monte_carlo.cpp)

target_include_directories(monte_carlo PUBLIC point)

add_subdirectory(point)

target_link_libraries(monte_carlo PUBLIC point)