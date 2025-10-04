#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H

#include <SFML/Graphics.hpp>
#include <stack> // Changed from <vector>
#include <memory>
#include "State.h"

namespace state {

    class StateManager {
    public:
        StateManager();
        ~StateManager() = default; // Explicitly declare destructor

        void pushState(std::unique_ptr<State> state);
        void popState();
        void changeState(std::unique_ptr<State> state);

        State* getActiveState(); // Added getActiveState()

        void handleInput(sf::Event& event); // Changed to sf::Event&
        void update(float deltaTime); // Changed to float
        void draw();

    private:
        std::stack<std::unique_ptr<State>> states; // Changed from std::vector
    };

} // State

#endif //PACMAN_STATEMANAGER_H
