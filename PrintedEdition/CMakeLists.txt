cmake_minimum_required(VERSION 3.23)

set(project "PrintedEdition")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
    PrintedEdition.cpp
    Magazine.cpp
    Book.cpp
    Textbook.cpp)

set(${project}_HEADERS
    PrintedEdition.h
    Magazine.h
    Book.h
    Textbook.h)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})
