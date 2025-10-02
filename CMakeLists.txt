cmake_minimum_required(VERSION 3.10)
project(PacMan)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(PacMan
        main.cpp
        world.cpp
        entity.cpp
        pacman.cpp
        entity.h
        pacman.h
        world.h
        enemy.cpp
        enemy.h
        wall.cpp
        wall.h
)
target_link_libraries(PacMan sfml-graphics sfml-window sfml-system)
