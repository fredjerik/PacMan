#include "Game.h"
#include "../Singleton/RenderWindow.h"
#include "Singleton/Stopwatch.h"
#include "State/MenuState.h"

Game::Game() {
    m_stateManager = std::make_unique<state::StateManager>();
    // Push MenuState onto stack
    m_stateManager->pushState(std::make_unique<state::MenuState>(m_stateManager.get()));
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