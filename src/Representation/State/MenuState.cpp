#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h" // To transition to LevelState
#include "../../Singleton/RenderWindow.h"
#include <iostream> // For error handling

// Forward declaration for AbstractFactory might be needed if not in a common header
// class AbstractFactory;
//
// namespace state
// {
//     MenuState::MenuState(StateManager* stateManager, AbstractFactory* factory)
//         : State(stateManager), factory_(factory)
//     {
//         // NOTE: You need to have a font file at this path in your project.
//         // You can create an 'assets' directory in your project root.
//         if (!font_.loadFromFile("assets/font.ttf"))
//         {
//             std::cerr << "Error: Could not load font from assets/font.ttf" << std::endl;
//         }
//
//         titleText_.setFont(font_);
//         titleText_.setString("Pac-Man");
//         titleText_.setCharacterSize(64);
//         sf::FloatRect textRect = titleText_.getLocalBounds();
//         titleText_.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
//         titleText_.setPosition(singleton::RenderWindow::getInstance().getView().getCenter().x, singleton::RenderWindow::getInstance().getView().getCenter().y - 100);
//
//
//         instructionText_.setFont(font_);
//         instructionText_.setString("Press Space to Start");
//         instructionText_.setCharacterSize(32);
//         textRect = instructionText_.getLocalBounds();
//         instructionText_.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
//         instructionText_.setPosition(singleton::RenderWindow::getInstance().getView().getCenter().x, singleton::RenderWindow::getInstance().getView().getCenter().y + 50);
//     }
//
//     void MenuState::handleInput(sf::Event& event)
//     {
//         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
//         {
//             // When space is pressed, change to a new LevelState
//             stateManager_->changeState(std::make_unique<LevelState>(stateManager_, factory_));
//         }
//     }
//
//     void MenuState::update(float deltaTime)
//     {
//         // Nothing to update in a static menu
//     }
//
//     void MenuState::draw()
//     {
//         singleton::RenderWindow::getInstance().draw(titleText_);
//         singleton::RenderWindow::getInstance().draw(instructionText_);
//     }
// }
