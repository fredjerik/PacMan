#include "VictoryState.h"
#include "StateManager.h"
#include "MenuState.h"
#include "LevelState.h"
#include "../../Singleton/RenderWindow.h"
#include <iostream>

namespace state {

    VictoryState::VictoryState(StateManager* stateManager, int score, int level)
        : State(stateManager), score_(score), level_(level) {

        if (!font_.loadFromFile("fonts/Pokemon.ttf")) {
            std::cerr << "Error: Could not load font from fonts/Pokemon.ttf" << std::endl;
        }

        initText();

        // Create semi-transparent background
        auto& window = singleton::RenderWindow::getInstance();
        background_.setSize(sf::Vector2f(window.getSize()));
        background_.setFillColor(sf::Color(0, 0, 0, 200)); // Semi-transparent black
    }

    void VictoryState::initText() {
        auto& window = singleton::RenderWindow::getInstance();
        sf::Vector2u windowSize = window.getSize();

        // Victory text
        victoryText_.setFont(font_);
        victoryText_.setString("VICTORY!");
        victoryText_.setCharacterSize(80);
        victoryText_.setFillColor(sf::Color::Green);
        victoryText_.setStyle(sf::Text::Bold);

        sf::FloatRect victoryBounds = victoryText_.getLocalBounds();
        victoryText_.setOrigin(victoryBounds.left + victoryBounds.width / 2.0f,
                              victoryBounds.top + victoryBounds.height / 2.0f);
        victoryText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.3f);

        // Score text
        scoreText_.setFont(font_);
        scoreText_.setString("Score: " + std::to_string(score_));
        scoreText_.setCharacterSize(40);
        scoreText_.setFillColor(sf::Color::Yellow);

        sf::FloatRect scoreBounds = scoreText_.getLocalBounds();
        scoreText_.setOrigin(scoreBounds.left + scoreBounds.width / 2.0f,
                            scoreBounds.top + scoreBounds.height / 2.0f);
        scoreText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.5f);

        // Level text
        levelText_.setFont(font_);
        levelText_.setString("Level: " + std::to_string(level_));
        levelText_.setCharacterSize(40);
        levelText_.setFillColor(sf::Color::Cyan);

        sf::FloatRect levelBounds = levelText_.getLocalBounds();
        levelText_.setOrigin(levelBounds.left + levelBounds.width / 2.0f,
                            levelBounds.top + levelBounds.height / 2.0f);
        levelText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.6f);

        // Instruction text
        instructionText_.setFont(font_);
        instructionText_.setString("Press SPACE for next level\nPress ESC for menu\nPress R to restart");
        instructionText_.setCharacterSize(30);
        instructionText_.setFillColor(sf::Color::White);
        instructionText_.setLineSpacing(1.5f);

        sf::FloatRect instructionBounds = instructionText_.getLocalBounds();
        instructionText_.setOrigin(instructionBounds.left + instructionBounds.width / 2.0f,
                                  instructionBounds.top + instructionBounds.height / 2.0f);
        instructionText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.8f);
    }

    void VictoryState::handleInput(sf::Event& event) {
        if (event.key.code == sf::Keyboard::Escape) {
            // Return to menu - pop VictoryState and any other states
            while (stateManager_->getActiveState() != nullptr) {
                stateManager_->popState();
                // Could check type instead, but this clears stack
            }
            stateManager_->pushState(std::make_unique<MenuState>(stateManager_));
        } else if (event.key.code == sf::Keyboard::Space) {
            // Next level - pop VictoryState, push new LevelState
            stateManager_->popState(); // Remove VictoryState
            stateManager_->pushState(std::make_unique<LevelState>(stateManager_, level_ + 1, score_));
        } else if (event.key.code == sf::Keyboard::R) {
            // Restart - pop VictoryState, push new LevelState
            stateManager_->popState(); // Remove VictoryState
            stateManager_->pushState(std::make_unique<LevelState>(stateManager_, level_, score_));
        }
    }

    void VictoryState::update(float deltaTime) {
        // Nothing to update in victory screen
    }

    void VictoryState::draw() {
        auto& window = singleton::RenderWindow::getInstance();
        window.clear(sf::Color::Black);

        // Draw background
        window.draw(background_);

        // Draw texts
        window.draw(victoryText_);
        window.draw(scoreText_);
        window.draw(levelText_);
        window.draw(instructionText_);
    }

} // namespace state