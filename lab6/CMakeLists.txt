cmake_minimum_required(VERSION 3.22.1)

project(lab6 C)

add_executable(lab6
        src/main.c)

find_path(LIBUSB_INCLUDE_DIR
        NAMES libusb.h)
find_library(LIBUSB_LIBRARY
        NAMES usb-1.0)

target_include_directories(lab6 PUBLIC ${LIBUSB_INCLUDE_DIR})
target_link_libraries(lab6 PUBLIC ${LIBUSB_LIBRARY})