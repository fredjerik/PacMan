#include "LevelState.h"

#include <iostream>

#include "StateManager.h"
#include "../../Singleton/RenderWindow.h"
#include "../FactorySFML.h"
#include "../View/SFMLRenderer.h"

namespace state {

    LevelState::LevelState(StateManager* stateManager)
        : State(stateManager),
          m_factory(std::make_unique<factory::FactorySFML>())
    {
        m_world = std::make_unique<logic::World>("debug_map.txt", m_factory.get());
        int grid_width = m_world->get_gridWidth();
        int grid_height = m_world->get_gridHeight();

        sf::RenderWindow& window = singleton::RenderWindow::getInstance();
        sf::Vector2u windowSize = window.getSize();

        m_camera = std::make_unique<Camera>(grid_width, grid_height, windowSize.x, windowSize.y);

        // Simple view that matches full window size
        m_gameView = sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
        m_gameView.setCenter(windowSize.x / 2.f, windowSize.y / 2.f);

        m_uiView = sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y));

        // TODO: Load font for UI here
        // TODO: Setup UI elements (score, lives, etc.) here
    }

    void LevelState::handleInput(sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                stateManager_->popState();
                exit(0); //remove when other states
            } else if (event.key.code == sf::Keyboard::D) {
                m_world->setPacManDirection(logic::Direction::Right);
            } else if (event.key.code == sf::Keyboard::A) {
                m_world->setPacManDirection(logic::Direction::Left);
            } else if (event.key.code == sf::Keyboard::W) {
                m_world->setPacManDirection(logic::Direction::Up);
            } else if (event.key.code == sf::Keyboard::S) {
                m_world->setPacManDirection(logic::Direction::Down);
            }
        }
    }


    void LevelState::update(float deltaTime) {
        m_world->update(deltaTime);
    }

    void LevelState::draw() {
        sf::RenderWindow& window = singleton::RenderWindow::getInstance();
        window.clear(sf::Color::Black);

        // --- Draw Game World ---
        window.setView(m_gameView);

        // Draw the walls
        for (const auto& pair : m_world->getWalls()) {
            const logic::Position& wallPos = pair.first;
            const logic::Size& wallSize = m_world->getLogicalTileSize();

            sf::RectangleShape wallShape;

            sf::Vector2f screenPos = m_camera->project(wallPos);
            float screenWidth = m_camera->projectScalarWidth(wallSize.width);
            float screenHeight = m_camera->projectScalarHeight(wallSize.height);

            wallShape.setPosition(screenPos);
            wallShape.setSize({screenWidth, screenHeight});
            wallShape.setFillColor(sf::Color::Blue);
            window.draw(wallShape);
        }

        representation::SFMLRenderer renderer(*m_camera);
        std::vector<logic::Observer*> observers = m_world->getObservers();
        for (logic::Observer* observer : observers) {
            observer->draw(renderer);
        }

        // --- Draw UI in black bars ---
        window.setView(m_uiView);

        // TODO: Update UI text (score, lives, etc.) here
        // TODO: Position UI elements based on camera offset
        // TODO: Draw UI elements in the black bars

        // Example structure:
        // 1. Get camera offset: m_camera->getViewOffset()
        // 2. Position score/lives in appropriate black bar area
        // 3. Draw decorative elements in black bars if desired
    }

} // state