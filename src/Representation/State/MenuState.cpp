#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"
#include "../../Singleton/RenderWindow.h"
#include <iostream>

namespace state {

    MenuState::MenuState(StateManager* stateManager)
        : State(stateManager) {

        if (!font_.loadFromFile("fonts/Pokemon.ttf")) {
            std::cerr << "Error: Could not load font from fonts/Pokemon.ttf" << std::endl;
        }

        initText();
    }

    void MenuState::initText() {
        auto& window = singleton::RenderWindow::getInstance();
        sf::Vector2u windowSize = window.getSize();

        // Title text
        titleText_.setFont(font_);
        titleText_.setString("PAC-MAN");
        titleText_.setCharacterSize(100);
        titleText_.setFillColor(sf::Color::Yellow);
        titleText_.setStyle(sf::Text::Bold);

        sf::FloatRect titleBounds = titleText_.getLocalBounds();
        titleText_.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
                            titleBounds.top + titleBounds.height / 2.0f);
        titleText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.3f);

        // Start option
        startText_.setFont(font_);
        startText_.setString("START GAME");
        startText_.setCharacterSize(50);
        startText_.setFillColor(sf::Color::Green); // Highlighted by default

        sf::FloatRect startBounds = startText_.getLocalBounds();
        startText_.setOrigin(startBounds.left + startBounds.width / 2.0f,
                            startBounds.top + startBounds.height / 2.0f);
        startText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.5f);

        // Quit option
        quitText_.setFont(font_);
        quitText_.setString("QUIT");
        quitText_.setCharacterSize(50);
        quitText_.setFillColor(sf::Color::White);

        sf::FloatRect quitBounds = quitText_.getLocalBounds();
        quitText_.setOrigin(quitBounds.left + quitBounds.width / 2.0f,
                           quitBounds.top + quitBounds.height / 2.0f);
        quitText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.6f);

        // Instruction text
        instructionText_.setFont(font_);
        instructionText_.setString("Use UP/DOWN to select, ENTER to confirm");
        instructionText_.setCharacterSize(25);
        instructionText_.setFillColor(sf::Color::Cyan);

        sf::FloatRect instructionBounds = instructionText_.getLocalBounds();
        instructionText_.setOrigin(instructionBounds.left + instructionBounds.width / 2.0f,
                                  instructionBounds.top + instructionBounds.height / 2.0f);
        instructionText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.8f);
    }

    void MenuState::handleInput(sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                selectedOption_ = 0;
                startText_.setFillColor(sf::Color::Green);
                quitText_.setFillColor(sf::Color::White);
            } else if (event.key.code == sf::Keyboard::Down) {
                selectedOption_ = 1;
                startText_.setFillColor(sf::Color::White);
                quitText_.setFillColor(sf::Color::Green);
            } else if (event.key.code == sf::Keyboard::Enter) {
                if (selectedOption_ == 0) {
                    // Start game at level 1
                    stateManager_->pushState(std::make_unique<LevelState>(stateManager_, 1, 0));
                } else if (selectedOption_ == 1) {
                    // Quit game
                    singleton::RenderWindow::getInstance().close();
                }
            }
        }
    }

    void MenuState::update(float deltaTime) {
        // Nothing to update in menu
    }

    void MenuState::draw() {
        auto& window = singleton::RenderWindow::getInstance();
        window.clear(sf::Color::Black);

        window.draw(titleText_);
        window.draw(startText_);
        window.draw(quitText_);
        window.draw(instructionText_);
    }

} // namespace state