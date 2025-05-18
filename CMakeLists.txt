cmake_minimum_required(VERSION 3.10)
project(STL_Examples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "include/*.cpp")

add_executable(STL_Examples main.cpp ${SOURCES})
