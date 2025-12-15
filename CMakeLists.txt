cmake_minimum_required(VERSION 3.10)
project(PacMan)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

file(GLOB_RECURSE LOGIC_SOURCES
    "src/Logic/*.cpp"
    "src/Singleton/*.cpp"
)

add_library(pacman_logic STATIC ${LOGIC_SOURCES})

target_include_directories(pacman_logic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SFML_SOURCES
        "src/Representation/*.cpp"
)

add_library(pacman_sfml STATIC ${SFML_SOURCES})

target_include_directories(pacman_sfml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(pacman_sfml PRIVATE pacman_logic sfml-graphics sfml-window sfml-system)

add_executable(PacMan src/main.cpp)

target_include_directories(PacMan PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(PacMan PRIVATE pacman_sfml)
