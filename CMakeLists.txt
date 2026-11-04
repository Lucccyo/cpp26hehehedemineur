cmake_minimum_required(VERSION 3.25)

project(Demineur
    VERSION 0.1.0
    DESCRIPTION "A C++ Minesweeper game"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(demineur main.cpp)

target_link_libraries(demineur PRIVATE stdc++exp)
