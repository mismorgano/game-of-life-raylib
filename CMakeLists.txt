cmake_minimum_required(VERSION 3.27)
project(game_of_life)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

find_package(raylib REQUIRED)

add_executable(game_of_life main.cpp
        src/World.h
        src/World.cpp
        )
target_link_libraries(game_of_life raylib)