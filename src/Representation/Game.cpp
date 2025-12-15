#include "Game.h"
#include "State/LevelState.h"
#include "../Singleton/RenderWindow.h"
#include "Singleton/Stopwatch.h"

Game::Game() {
    // Initialize the StateManager. Game owns the StateManager.
    m_stateManager = std::make_unique<state::StateManager>();

    // Push the initial state (LevelState) onto the stack.
    // LevelState will be responsible for creating the factory and its world.
    m_stateManager->pushState(std::make_unique<state::LevelState>(m_stateManager.get()));

    // Initialize the stopwatch
    singleton::Stopwatch::get_instance().start();
}

void Game::run() {

    // float deltaTime = singleton::Stopwatch::get_instance().tick(); // Get deltaTime from stopwatch
    // handleEvents();
    // update(deltaTime); // Pass float deltaTime
    // render();
    /**
     * actual game
     */
    while (singleton::RenderWindow::getInstance().isOpen()) {
        float deltaTime = singleton::Stopwatch::get_instance().tick(); // Get deltaTime from stopwatch
        handleEvents();
        update(deltaTime); // Pass float deltaTime
        render();
    }
    singleton::Stopwatch::get_instance().stop(); // Stop the stopwatch when the Game ends
}

void Game::handleEvents() {
    sf::Event event{};
    while (singleton::RenderWindow::getInstance().pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            singleton::RenderWindow::getInstance().close();

        // Delegate event handling to the active State
        m_stateManager->handleInput(event);
    }
}

void Game::update(float deltaTime) {
    // Delegate updating to the active State
    m_stateManager->update(deltaTime);
}

void Game::render() {
    singleton::RenderWindow::getInstance().clear();
    // Delegate drawing to the active State
    m_stateManager->draw();
    singleton::RenderWindow::getInstance().display();
}