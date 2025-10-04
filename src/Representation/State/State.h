#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace state {

    class StateManager; // Forward declaration

    class State {
    public:
        explicit State(StateManager* state_manager) : stateManager_(state_manager) {}
        virtual ~State() = default;

        virtual void handleInput(sf::Event& event) = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw() = 0;

    protected:
        StateManager* stateManager_;
    };

} // State

#endif //PACMAN_STATE_H
