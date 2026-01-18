#include "Game.h"
#include "../Singleton/RenderWindow.h"
#include "Singleton/Stopwatch.h"
#include "State/MenuState.h"

Game::Game() {
    m_stateManager = std::make_unique<state::StateManager>();
    m_stateManager->pushState(std::make_unique<state::MenuState>(m_stateManager.get()));
}

void Game::run() {

    while (singleton::RenderWindow::getInstance().isOpen()) {
        float deltaTime = singleton::Stopwatch::get_instance().tick();
        handleEvents();
        update(deltaTime);
        render();
    }
    singleton::Stopwatch::get_instance().stop();
}

void Game::handleEvents() {
    sf::Event event{};
    while (singleton::RenderWindow::getInstance().pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            singleton::RenderWindow::getInstance().close();

        m_stateManager->handleInput(event);
    }
}

void Game::update(float deltaTime) {
    m_stateManager->update(deltaTime);
}

void Game::render() {
    singleton::RenderWindow::getInstance().clear();
    m_stateManager->draw();
    singleton::RenderWindow::getInstance().display();
}