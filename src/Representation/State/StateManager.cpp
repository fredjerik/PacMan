#include "StateManager.h"
#include "../../Singleton/RenderWindow.h"
#include <stack> // Assuming states is a stack

namespace state {

    StateManager::StateManager() = default;
    // Removed StateManager::~StateManager() = default;

    void StateManager::pushState(std::unique_ptr<State> state) {
        states.push(std::move(state));
    }

    void StateManager::popState() {
        if (!states.empty()) {
            states.pop();
        }
    }

    void StateManager::changeState(std::unique_ptr<State> state) {
        if (!states.empty()) {
            popState();
        }
        pushState(std::move(state));
    }

    State* StateManager::getActiveState() {
        if (states.empty()) {
            return nullptr;
        }
        return states.top().get();
    }

    void StateManager::handleInput(sf::Event& event) { // Changed to sf::Event&
        if (State* activeState = getActiveState()) {
            activeState->handleInput(event);
        }
    }

    void StateManager::update(float deltaTime) { // Changed to float
        if (State* activeState = getActiveState()) {
            activeState->update(deltaTime);
        }
    }

    void StateManager::draw() { // Removed sf::RenderWindow& window parameter
        if (State* activeState = getActiveState()) {
            activeState->draw(); // Call draw without window parameter
        }
    }

}
