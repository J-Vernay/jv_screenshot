cmake_minimum_required(VERSION 3.0.0)
project(jv_screenshot VERSION 0.1.0)

find_package(X11 REQUIRED)

add_library(jv_screenshot jv_screenshot.c)
target_link_libraries(jv_screenshot PRIVATE X11)
target_include_directories(jv_screenshot PUBLIC .)

