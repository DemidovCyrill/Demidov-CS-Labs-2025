cmake_minimum_required(VERSION 3.23)

set(project "include")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
    polynomial.cpp
    term.cpp)

set(${project}_HEADERS
    string_examples.h
    vector_examples.h
    list_examples.h
    map_examples.h
    string_examples.cpp
    vector_examples.cpp
    list_examples.cpp
    map_examples.cpp
)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})
