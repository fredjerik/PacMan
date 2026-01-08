#include "GhostView.h"
#include "Singleton/Stopwatch.h"
#include <iostream>

namespace view
{
    GhostView::GhostView(std::weak_ptr<logic::GhostEntity> model,
                        int normalSpriteX, int normalSpriteY)
        : EntityView(model, sf::IntRect(normalSpriteX, normalSpriteY, 35, 35))
    {
        setupFrames(normalSpriteX, normalSpriteY);
    }

    void GhostView::setupFrames(int normalSpriteX, int normalSpriteY) {
        // Initialize all frames
        // Mode 0: Normal (colored ghosts)
        // Mode 1: Fear (solid blue)
        // Mode 2: Fear flashing (blue/white alternating)
        // Mode 3: Eaten (just eyes)

        // NORMAL mode frames (colored ghost)
        // Up direction: 2 frames for animation
        frames_[0][0].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 300, 35, 35));     // Up frame 1
        frames_[0][0].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 300, 35, 35));     // Up frame 1
        frames_[0][0].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 350, 35, 35));     // Up frame 2
        frames_[0][0].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 350, 35, 35));     // Up frame 2

        // Left direction
        frames_[0][1].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 200, 35, 35));     // Left frame 1
        frames_[0][1].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 200, 35, 35));     // Left frame 1
        frames_[0][1].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 250, 35, 35));     // Left frame 2
        frames_[0][1].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 250, 35, 35));     // Left frame 2

        // Down direction
        frames_[0][2].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 100, 35, 35));     // Down frame 1
        frames_[0][2].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 100, 35, 35));     // Down frame 1
        frames_[0][2].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 150, 35, 35));     // Down frame 2
        frames_[0][2].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 150, 35, 35));     // Down frame 2

        // Right direction
        frames_[0][3].push_back(sf::IntRect(normalSpriteX, normalSpriteY, 35, 35));           // Right frame 1
        frames_[0][3].push_back(sf::IntRect(normalSpriteX, normalSpriteY, 35, 35));           // Right frame 1
        frames_[0][3].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 50, 35, 35));      // Right frame 2
        frames_[0][3].push_back(sf::IntRect(normalSpriteX, normalSpriteY + 50, 35, 35));      // Right frame 2

        // FEAR mode frames - SOLID BLUE (mode 1)
        // Up - blue
        frames_[1][0].push_back(sf::IntRect(2, 554, 35, 35));      // Blue up frame 1
        frames_[1][0].push_back(sf::IntRect(2, 554, 35, 35));      // Blue up frame 1
        frames_[1][0].push_back(sf::IntRect(2, 604, 35, 35));      // Blue up frame 2
        frames_[1][0].push_back(sf::IntRect(2, 604, 35, 35));      // Blue up frame 2

        // Left - blue
        frames_[1][1].push_back(sf::IntRect(2, 554, 35, 35));      // Blue left frame 1
        frames_[1][1].push_back(sf::IntRect(2, 554, 35, 35));      // Blue left frame 1
        frames_[1][1].push_back(sf::IntRect(2, 604, 35, 35));      // Blue left frame 2
        frames_[1][1].push_back(sf::IntRect(2, 604, 35, 35));      // Blue left frame 2

        // Down - blue
        frames_[1][2].push_back(sf::IntRect(2, 554, 35, 35));      // Blue down frame 1
        frames_[1][2].push_back(sf::IntRect(2, 554, 35, 35));      // Blue down frame 1
        frames_[1][2].push_back(sf::IntRect(2, 604, 35, 35));      // Blue down frame 2
        frames_[1][2].push_back(sf::IntRect(2, 604, 35, 35));      // Blue down frame 2

        // Right - blue
        frames_[1][3].push_back(sf::IntRect(52, 554, 35, 35));     // Blue right frame 1
        frames_[1][3].push_back(sf::IntRect(52, 554, 35, 35));     // Blue right frame 1
        frames_[1][3].push_back(sf::IntRect(52, 604, 35, 35));     // Blue right frame 2
        frames_[1][3].push_back(sf::IntRect(52, 604, 35, 35));     // Blue right frame 2

        // FEAR FLASHING mode frames - BLUE/WHITE ALTERNATING (mode 2)
        // Up - blue then white
        frames_[2][0].push_back(sf::IntRect(2, 554, 35, 35));
        frames_[2][0].push_back(sf::IntRect(2, 604, 35, 35));
        frames_[2][0].push_back(sf::IntRect(52, 554, 35, 35));
        frames_[2][0].push_back(sf::IntRect(52, 604, 35, 35));

        // Left - blue then white
        frames_[2][1].push_back(sf::IntRect(2, 554, 35, 35));      // Blue left
        frames_[2][1].push_back(sf::IntRect(2, 604, 35, 35));      // Blue left
        frames_[2][1].push_back(sf::IntRect(52, 554, 35, 35));     // White left
        frames_[2][1].push_back(sf::IntRect(52, 604, 35, 35));     // White left

        // Down - blue then white
        frames_[2][2].push_back(sf::IntRect(2, 554, 35, 35));      // Blue down
        frames_[2][2].push_back(sf::IntRect(2, 604, 35, 35));      // Blue down
        frames_[2][2].push_back(sf::IntRect(52, 554, 35, 35));    // White down
        frames_[2][2].push_back(sf::IntRect(52, 604, 35, 35));    // White down

        // Right - blue then white
        frames_[2][3].push_back(sf::IntRect(52, 554, 35, 35));     // Blue right
        frames_[2][3].push_back(sf::IntRect(52, 604, 35, 35));     // Blue right
        frames_[2][3].push_back(sf::IntRect(52, 554, 35, 35));    // White right
        frames_[2][3].push_back(sf::IntRect(52, 604, 35, 35));    // White right

        // EATEN mode frames (just eyes) - mode 3
        int eyesX = 302;
        frames_[3][0].push_back(sf::IntRect(eyesX, 404, 35, 35));      // Eyes up
        frames_[3][1].push_back(sf::IntRect(eyesX, 354, 35, 35));      // Eyes left
        frames_[3][2].push_back(sf::IntRect(eyesX, 304, 35, 35));      // Eyes down
        frames_[3][3].push_back(sf::IntRect(eyesX, 254, 35, 35));      // Eyes right
    }

    void GhostView::updateAnimation() {
        static int frameCounter = 0;
        frameCounter++;

        if (frameCounter % 3 == 0) {
            // Get direction index
            int dirIndex = 1; // Default: Left
            switch (currentDirection_) {
                case logic::Direction::Up: dirIndex = 0; break;
                case logic::Direction::Left: dirIndex = 1; break;
                case logic::Direction::Down: dirIndex = 2; break;
                case logic::Direction::Right: dirIndex = 3; break;
                default: dirIndex = 1; break;
            }

            // Get frames for current mode and direction
            auto& currentFrames = frames_[currentMode_][dirIndex];

            if (!currentFrames.empty()) {
                currentFrame_ = (currentFrame_ + 1) % currentFrames.size();

                sprite_.setTextureRect(currentFrames[currentFrame_]);
            }
        }

        // Reset counter periodically
        if (frameCounter > 1000) frameCounter = 0;
    }

    void GhostView::onGameEvent(logic::GameEvent event, int data) {
        switch (event) {
            case logic::GameEvent::GhostModeChanged:
                // 0 = normal mode
                // 1 = fear mode (solid blue)
                // 2 = fear flashing mode (blue/white alternating)
                // 3 = eaten mode
                if (data >= 0 && data <= 3) {
                    currentMode_ = data;
                    currentFrame_ = 0; // Reset animation frame

                    // Update immediately to new mode
                    int dirIndex = 1; // Default: Left
                    switch (currentDirection_) {
                        case logic::Direction::Up: dirIndex = 0; break;
                        case logic::Direction::Left: dirIndex = 1; break;
                        case logic::Direction::Down: dirIndex = 2; break;
                        case logic::Direction::Right: dirIndex = 3; break;
                    }

                    auto& frames = frames_[currentMode_][dirIndex];
                    if (!frames.empty()) {
                        sprite_.setTextureRect(frames[0]);
                    }
                }
                break;

            case logic::GameEvent::DirectionChanged:
                if (data >= 0 && data <= 4) {
                    logic::Direction newDir = static_cast<logic::Direction>(data);
                    if (currentDirection_ != newDir) {
                        currentDirection_ = newDir;
                        currentFrame_ = 0; // Reset animation frame

                        // Update immediately to new direction
                        int dirIndex = 1; // Default: Left
                        switch (currentDirection_) {
                            case logic::Direction::Up: dirIndex = 0; break;
                            case logic::Direction::Left: dirIndex = 1; break;
                            case logic::Direction::Down: dirIndex = 2; break;
                            case logic::Direction::Right: dirIndex = 3; break;
                        }

                        auto& frames = frames_[currentMode_][dirIndex];
                        if (!frames.empty()) {
                            sprite_.setTextureRect(frames[0]);
                        }
                    }
                }
                break;
        }
    }

    // Concrete ghost classes
    BlinkyView::BlinkyView(std::weak_ptr<logic::BlinkyEntity> model)
        : GhostView(model, 0, 4) {}

    PinkyView::PinkyView(std::weak_ptr<logic::PinkyEntity> model)
        : GhostView(model, 50, 4) {}

    InkyView::InkyView(std::weak_ptr<logic::InkyEntity> model)
        : GhostView(model, 100, 4) {}

    ClydeView::ClydeView(std::weak_ptr<logic::ClydeEntity> model)
        : GhostView(model, 150, 4) {}
} // view