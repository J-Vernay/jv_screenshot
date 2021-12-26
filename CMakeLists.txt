cmake_minimum_required(VERSION 3.0.0)
project(jv_screenshot_example VERSION 0.1.0)

add_subdirectory(jv_screenshot)

add_executable(jv_screenshot_example example.c)
target_link_libraries(jv_screenshot_example PRIVATE jv_screenshot)

