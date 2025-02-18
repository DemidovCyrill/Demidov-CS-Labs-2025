cmake_minimum_required(VERSION 3.23)

set(project "lab3")
project(${project})

set(CMAKE_CXX_STANDARD 17)

# Добавляем путь к заголовочным файлам
include_directories(${CMAKE_SOURCE_DIR}/include)

# Добавляем путь к библиотеке
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(${project}_SOURCES
        main.cpp)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})

target_link_libraries(${project}
    mymath)  # Линкуем с библиотекой mymath.a
