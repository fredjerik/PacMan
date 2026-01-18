#include "GhostView.h"
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
        // NORMAL mode frames (colored ghost) - 2 frames each
        normalUpFrames.emplace_back(normalSpriteX, normalSpriteY + 300, 35, 35);
        normalUpFrames.emplace_back(normalSpriteX, normalSpriteY + 350, 35, 35);

        normalLeftFrames.emplace_back(normalSpriteX, normalSpriteY + 200, 35, 35);
        normalLeftFrames.emplace_back(normalSpriteX, normalSpriteY + 250, 35, 35);

        normalDownFrames.emplace_back(normalSpriteX, normalSpriteY + 100, 35, 35);
        normalDownFrames.emplace_back(normalSpriteX, normalSpriteY + 150, 35, 35);

        normalRightFrames.emplace_back(normalSpriteX, normalSpriteY, 35, 35);
        normalRightFrames.emplace_back(normalSpriteX, normalSpriteY + 50, 35, 35);

        // FEAR mode frames (solid blue) - 2 frames
        fearFrames.emplace_back(2, 554, 35, 35);
        fearFrames.emplace_back(2, 604, 35, 35);

        // FEAR FLASHING mode frames (blue/white alternating) - 4 frames
        fearFlashingFrames.emplace_back(2, 554, 35, 35);   // Blue 1
        fearFlashingFrames.emplace_back(2, 604, 35, 35);   // Blue 2
        fearFlashingFrames.emplace_back(52, 554, 35, 35);  // White 1
        fearFlashingFrames.emplace_back(52, 604, 35, 35);  // White 2

        // EATEN mode frames (just eyes) - 1 frame each
        int eyesX = 302;
        eatenUpFrames.emplace_back(eyesX, 404, 35, 35);
        eatenLeftFrames.emplace_back(eyesX, 354, 35, 35);
        eatenDownFrames.emplace_back(eyesX, 304, 35, 35);
        eatenRightFrames.emplace_back(eyesX, 254, 35, 35);
    }

    const std::vector<sf::IntRect>& GhostView::getCurrentFrames() const {
        switch (currentMode_) {
            case 0: // Normal mode
                switch (currentDirection_) {
                    case logic::Direction::Up: return normalUpFrames;
                    case logic::Direction::Left: return normalLeftFrames;
                    case logic::Direction::Down: return normalDownFrames;
                    case logic::Direction::Right: return normalRightFrames;
                    default: return normalLeftFrames;
                }

            case 1: // Fear mode
                return fearFrames;

            case 2: // Fear flashing mode
                return fearFlashingFrames;

            case 3: // Eaten mode
                switch (currentDirection_) {
                    case logic::Direction::Up: return eatenUpFrames;
                    case logic::Direction::Left: return eatenLeftFrames;
                    case logic::Direction::Down: return eatenDownFrames;
                    case logic::Direction::Right: return eatenRightFrames;
                    default: return eatenLeftFrames;
                }

            default:
                return normalLeftFrames;
        }
    }

    void GhostView::updateAnimation() {
        frameCounter_++;

        int framesBetweenUpdates = 5;

        if (frameCounter_ % framesBetweenUpdates == 0) {
            const std::vector<sf::IntRect>& currentFrames = getCurrentFrames();

            if (!currentFrames.empty()) {
                currentFrame_ = (currentFrame_ + 1) % currentFrames.size();
                sprite_.setTextureRect(currentFrames[currentFrame_]);
            }
        }

        if (frameCounter_ > 10000) frameCounter_ = 0;
    }

    void GhostView::onGameEvent(logic::GameEvent event, int data) {
        switch (event) {
            case logic::GameEvent::GhostModeChanged:
                if (data >= 0 && data <= 3) {
                    currentMode_ = data;
                    currentFrame_ = 0;

                    const std::vector<sf::IntRect>& frames = getCurrentFrames();
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
                        currentFrame_ = 0;

                        const std::vector<sf::IntRect>& frames = getCurrentFrames();
                        if (!frames.empty()) {
                            sprite_.setTextureRect(frames[0]);
                        }
                    }
                }
                break;
        }
    }

    BlinkyView::BlinkyView(std::weak_ptr<logic::BlinkyEntity> model)
        : GhostView(model, 0, 4) {}

    PinkyView::PinkyView(std::weak_ptr<logic::PinkyEntity> model)
        : GhostView(model, 50, 4) {}

    InkyView::InkyView(std::weak_ptr<logic::InkyEntity> model)
        : GhostView(model, 100, 4) {}

    ClydeView::ClydeView(std::weak_ptr<logic::ClydeEntity> model)
        : GhostView(model, 150, 4) {}
} // view