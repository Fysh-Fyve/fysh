cmake_minimum_required(VERSION 3.21)

project(Fysh)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

add_executable(fysh src/main.cc)
target_link_libraries(fysh common)

add_subdirectory(test)
