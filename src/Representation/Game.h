#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "State/StateManager.h"
#include <memory>

class Game {
public:
    Game();
    void run();

private:
    void handleEvents();
    void update(float deltaTime);
    void render();

    std::unique_ptr<state::StateManager> m_stateManager;
};

#endif //PACMAN_GAME_H