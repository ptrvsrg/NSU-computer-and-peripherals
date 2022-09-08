add_executable(lab1 main.cpp)

target_include_directories(lab1 PRIVATE monte_carlo)

add_subdirectory(monte_carlo)

target_link_libraries(lab1 PRIVATE monte_carlo)