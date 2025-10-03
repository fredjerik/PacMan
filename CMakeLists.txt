cmake_minimum_required(VERSION 3.10)
project(PacMan)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(PacMan
        src/main.cpp
        src/entity.h
        src/entity.cpp
        src/pacman.h
        src/pacman.cpp
        src/game.h
        src/game.cpp
        src/dynamic_entity.h
        src/dynamic_entity.cpp
)
target_link_libraries(PacMan sfml-graphics sfml-window sfml-system)
