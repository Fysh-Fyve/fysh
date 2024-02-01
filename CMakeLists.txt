cmake_minimum_required(VERSION 3.21)

project(Fysh)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Gotta go fast
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_subdirectory(src)

add_executable(fysh src/main.cc)
target_link_libraries(fysh common)

add_subdirectory(test)
