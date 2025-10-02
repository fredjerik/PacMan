cmake_minimum_required(VERSION 3.10)
project(PacMan)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(PacMan
        src/main.cpp
        src/world.cpp
        src/entity.cpp
        src/pacman.cpp
        src/entity.h
        src/pacman.h
        src/world.h
        src/enemy.cpp
        src/enemy.h
        src/wall.cpp
        src/wall.h
)
target_link_libraries(PacMan sfml-graphics sfml-window sfml-system)
