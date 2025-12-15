#include "Representation/Game.h"
#include <iostream>

int main() {
    try {
        Game main_game;
        main_game.run();
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}