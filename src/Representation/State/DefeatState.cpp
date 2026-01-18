#include "DefeatState.h"
#include "StateManager.h"
#include "MenuState.h"
#include "LevelState.h"
#include "../../Singleton/RenderWindow.h"
#include <iostream>

namespace state {

    DefeatState::DefeatState(StateManager* stateManager, int score, int level)
        : State(stateManager), score_(score), level_(level) {

        if (!font_.loadFromFile("fonts/Pokemon.ttf")) {
            std::cerr << "Error: Could not load font from fonts/Pokemon.ttf" << std::endl;
        }

        initText();

        auto& window = singleton::RenderWindow::getInstance();
        background_.setSize(sf::Vector2f(window.getSize()));
        background_.setFillColor(sf::Color(0, 0, 0, 200)); // Semi-transparent black
    }

    void DefeatState::initText() {
        auto& window = singleton::RenderWindow::getInstance();
        sf::Vector2u windowSize = window.getSize();

        defeatText_.setFont(font_);
        defeatText_.setString("GAME OVER");
        defeatText_.setCharacterSize(80);
        defeatText_.setFillColor(sf::Color::Red);
        defeatText_.setStyle(sf::Text::Bold);

        sf::FloatRect defeatBounds = defeatText_.getLocalBounds();
        defeatText_.setOrigin(defeatBounds.left + defeatBounds.width / 2.0f,
                             defeatBounds.top + defeatBounds.height / 2.0f);
        defeatText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.3f);

        scoreText_.setFont(font_);
        scoreText_.setString("Score: " + std::to_string(score_));
        scoreText_.setCharacterSize(40);
        scoreText_.setFillColor(sf::Color::Yellow);

        const sf::FloatRect scoreBounds = scoreText_.getLocalBounds();
        scoreText_.setOrigin(scoreBounds.left + scoreBounds.width / 2.0f,
                            scoreBounds.top + scoreBounds.height / 2.0f);
        scoreText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.5f);

        levelText_.setFont(font_);
        levelText_.setString("Level: " + std::to_string(level_));
        levelText_.setCharacterSize(40);
        levelText_.setFillColor(sf::Color::Cyan);

        sf::FloatRect levelBounds = levelText_.getLocalBounds();
        levelText_.setOrigin(levelBounds.left + levelBounds.width / 2.0f,
                            levelBounds.top + levelBounds.height / 2.0f);
        levelText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.6f);

        instructionText_.setFont(font_);
        instructionText_.setString("Press SPACE to retry\nPress ESC for menu");
        instructionText_.setCharacterSize(30);
        instructionText_.setFillColor(sf::Color::White);
        instructionText_.setLineSpacing(1.5f);

        sf::FloatRect instructionBounds = instructionText_.getLocalBounds();
        instructionText_.setOrigin(instructionBounds.left + instructionBounds.width / 2.0f,
                                  instructionBounds.top + instructionBounds.height / 2.0f);
        instructionText_.setPosition(windowSize.x / 2.0f, windowSize.y * 0.8f);
    }

    void DefeatState::handleInput(sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {

            if (event.key.code == sf::Keyboard::Escape) {
                stateManager_->changeState(std::make_unique<MenuState>(stateManager_));
            }

            else if (event.key.code == sf::Keyboard::Space) {
                stateManager_->changeState(std::make_unique<LevelState>(stateManager_, 1, 0));
            }
        }
    }

    void DefeatState::draw() {
        auto& window = singleton::RenderWindow::getInstance();
        window.clear(sf::Color::Black);

        window.draw(background_);

        window.draw(defeatText_);
        window.draw(scoreText_);
        window.draw(levelText_);
        window.draw(instructionText_);
    }

} // namespace state