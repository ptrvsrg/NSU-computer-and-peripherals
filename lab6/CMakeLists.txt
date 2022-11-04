cmake_minimum_required(VERSION 3.16.3)

project(lab6 C)

add_executable(lab6
        src/main.c)

find_package(PkgConfig)
pkg_check_modules(libusb-1.0 REQUIRED libusb-1.0)

target_include_directories(lab6 PUBLIC
        ${libusb-1.0_INCLUDE_DIRS})
target_link_libraries(lab6 PUBLIC
        ${libusb-1.0_LIBRARIES})