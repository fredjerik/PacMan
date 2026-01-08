#include "PausedState.h"
#include "StateManager.h"
#include "MenuState.h"
#include "../../Singleton/RenderWindow.h"
#include <iostream>

namespace state {

    PauseState::PauseState(StateManager* stateManager)
        : State(stateManager) {

        if (!font_.loadFromFile("fonts/Pokemon.ttf")) {
            std::cerr << "Error: Could not load font from fonts/Pokemon.ttf" << std::endl;
        }

        initText();

        // Create semi-transparent background
        auto& window = singleton::RenderWindow::getInstance();
        background_.setSize(sf::Vector2f(window.getSize()));
        background_.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black
    }

    void PauseState::initText() {
        auto& window = singleton::RenderWindow::getInstance();
        sf::Vector2u windowSize = window.getSize();

        // Pause text
        pauseText_.setFont(font_);
        pauseText_.setString("PAUSED");
        pauseText_.setCharacterSize(80);
        pauseText_.setFillColor(sf::Color::Yellow);
        pauseText_.setStyle(sf::Text::Bold);

        sf::FloatRect pauseBounds = pauseText_.getLocalBounds();
        pauseText_.setOrigin(pauseBounds.left + pauseBounds.width / 2.0f,
                            pauseBounds.top + pauseBounds.height / 2.0f);
        pauseText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.3f);

        // Resume option
        resumeText_.setFont(font_);
        resumeText_.setString("RESUME");
        resumeText_.setCharacterSize(50);
        resumeText_.setFillColor(sf::Color::Green); // Highlighted by default

        sf::FloatRect resumeBounds = resumeText_.getLocalBounds();
        resumeText_.setOrigin(resumeBounds.left + resumeBounds.width / 2.0f,
                             resumeBounds.top + resumeBounds.height / 2.0f);
        resumeText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.45f);

        // Quit option
        quitText_.setFont(font_);
        quitText_.setString("QUIT");
        quitText_.setCharacterSize(50);
        quitText_.setFillColor(sf::Color::White);

        sf::FloatRect quitBounds = quitText_.getLocalBounds();
        quitText_.setOrigin(quitBounds.left + quitBounds.width / 2.0f,
                           quitBounds.top + quitBounds.height / 2.0f);
        quitText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.55f);

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

    void PauseState::handleInput(sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                // Resume game - pop the pause state
                stateManager_->popState();
            } else if (event.key.code == sf::Keyboard::Up) {
                selectedOption_ = (selectedOption_ - 1 + 2) % 2; // 3 options
                updateSelection();
            } else if (event.key.code == sf::Keyboard::Down) {
                selectedOption_ = (selectedOption_ + 1) % 2; // 3 options
                updateSelection();
            } else if (event.key.code == sf::Keyboard::Enter) {
                executeSelectedOption();
            }
        }
    }

    void PauseState::updateSelection() {
        // Reset all colors to white
        resumeText_.setFillColor(sf::Color::White);
        quitText_.setFillColor(sf::Color::White);

        // Highlight selected option
        switch (selectedOption_) {
            case 0: resumeText_.setFillColor(sf::Color::Green); break;
            case 1: quitText_.setFillColor(sf::Color::Green); break;
        }
    }

    void PauseState::executeSelectedOption() {
        switch (selectedOption_) {
        case 0: // Resume
            stateManager_->popState(); // Pop PauseState, revealing LevelState
            break;
        case 1: // Quit
            singleton::RenderWindow::getInstance().close();
            break;
        }
    }

    void PauseState::update(float deltaTime) {
        // Nothing to update in pause screen
    }

    void PauseState::draw() {
        auto& window = singleton::RenderWindow::getInstance();

        // Note: We don't clear the screen because we want to see the paused game behind
        // The game state will have already drawn the game world

        // Draw semi-transparent overlay
        window.draw(background_);

        // Draw pause menu texts
        window.draw(pauseText_);
        window.draw(resumeText_);
        window.draw(quitText_);
        window.draw(instructionText_);
    }

} // namespace state