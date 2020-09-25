cmake_minimum_required(VERSION 3.17)
project(IA_Proj1)

set(CMAKE_CXX_STANDARD 17)


# Include the include directory that contains the hpp files
include_directories(include)

# Declare some nice flags
set(GCC_COVERAGE_COMPILE_FLAGS "-fsanitize=address,undefined -Wall -ggdb3")
set(GCC_COVERAGE_LINK_FLAGS    "-fsanitize=address,undefined")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(IA_Proj1 src/main.cpp src/Coordinate.cpp src/Graph.cpp)

add_definitions(-DLOCAL_DEFINE)