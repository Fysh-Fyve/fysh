cmake_minimum_required(VERSION 3.21)

project(Fysh)

# Add LLVM to the project
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

llvm_map_components_to_libnames(llvm_libs support core orcjit native irreader)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Gotta go fast
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_subdirectory(src)

add_executable(fysh src/main.cc)
target_link_libraries(fysh common ${llvm_libs})

add_subdirectory(test)
