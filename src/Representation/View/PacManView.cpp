#include "PacManView.h"
#include <SFML/Graphics/Rect.hpp>
#include "Singleton/Stopwatch.h"
#include <iostream>

namespace view
{
    PacManView::PacManView(std::weak_ptr<logic::PacmanEntity> model)
    : EntityView(model, sf::IntRect(852, 4, 35, 35)) // Start with mouth closed, facing right
    {
        std::cout << "PacManView: Loading animation frames..." << std::endl;

        // Right direction frames (mouth opening to the right)
        right_frames_.push_back(sf::IntRect(852, 4, 35, 35));   // Frame 1: almost closed
        right_frames_.push_back(sf::IntRect(852, 54, 35, 35));  // Frame 2: half open
        right_frames_.push_back(sf::IntRect(852, 104, 35, 35)); // Frame 3: fully open

        // Left direction frames (mouth opening to the left)
        left_frames_.push_back(sf::IntRect(852, 304, 35, 35));  // Frame 1: almost closed
        left_frames_.push_back(sf::IntRect(852, 354, 35, 35));  // Frame 2: half open
        left_frames_.push_back(sf::IntRect(852, 404, 35, 35));  // Frame 3: fully open

        // Up direction frames
        up_frames_.push_back(sf::IntRect(852, 454, 35, 35));    // Frame 1: almost closed
        up_frames_.push_back(sf::IntRect(852, 504, 35, 35));    // Frame 2: half open
        up_frames_.push_back(sf::IntRect(852, 554, 35, 35));    // Frame 3: fully open

        // Down direction frames
        down_frames_.push_back(sf::IntRect(852, 154, 35, 35));  // Frame 1: almost closed
        down_frames_.push_back(sf::IntRect(852, 204, 35, 35));  // Frame 2: half open
        down_frames_.push_back(sf::IntRect(852, 254, 35, 35));  // Frame 3: fully open

        // Death animation frames
        death_frames_.push_back(sf::IntRect(352, 4, 35, 35));   // Death frame 1
        death_frames_.push_back(sf::IntRect(352, 54, 35, 35));  // Death frame 2
        death_frames_.push_back(sf::IntRect(352, 104, 35, 35)); // Death frame 3
        death_frames_.push_back(sf::IntRect(352, 154, 35, 35)); // Death frame 4
        death_frames_.push_back(sf::IntRect(352, 204, 35, 35)); // Death frame 5
        death_frames_.push_back(sf::IntRect(352, 254, 35, 35)); // Death frame 6
        death_frames_.push_back(sf::IntRect(352, 304, 35, 35)); // Death frame 7
        death_frames_.push_back(sf::IntRect(352, 354, 35, 35)); // Death frame 8
        death_frames_.push_back(sf::IntRect(352, 404, 35, 35)); // Death frame 9
        death_frames_.push_back(sf::IntRect(352, 454, 35, 35)); // Death frame 10
        death_frames_.push_back(sf::IntRect(352, 504, 35, 35)); // Death frame 11
        death_frames_.push_back(sf::IntRect(0, 0, 0, 0)); // Death frame 12
        death_frames_.push_back(sf::IntRect(0, 0, 0, 0)); // Death frame 12
        death_frames_.push_back(sf::IntRect(0, 0, 0, 0)); // Death frame 12
        death_frames_.push_back(sf::IntRect(0, 0, 0, 0)); // Death frame 12

        frameDuration_ = 0.1f; // 10 frames per second for normal animation
        deathFrameDuration_ = 0.08f; // Slower for death animation
        isPlayingDeathAnimation_ = false;
        deathAnimationComplete_ = false;
        std::cout << "PacManView: Animation frames loaded successfully!" << std::endl;
    }

    void PacManView::updateAnimation() {
        float targetFPS = singleton::Stopwatch::get_instance().get_target_fps();
        if (targetFPS <= 0) targetFPS = 60.0f;

        // Calculate how many game frames per animation frame
        // At 60 FPS: 60/12.5 = ~5 frames between animation updates
        // At 30 FPS: 30/12.5 = ~2.4 frames between animation updates
        float animationFPS = 12.5f; // Target animation speed
        static float framesPerAnimationUpdate = targetFPS / animationFPS;
        static int frameCounter = 0;

        frameCounter++;

        // Death animation
        if (isPlayingDeathAnimation_) {
            // Update death animation slower (~8 FPS)
            if (frameCounter % static_cast<int>(targetFPS / 8.0f) == 0) {
                currentFrame_++;

                // Loop back to start if out of bounds
                if (currentFrame_ >= death_frames_.size()) {
                    isPlayingDeathAnimation_ = false;
                    deathAnimationComplete_ = true;
                    sprite_.setTextureRect(sf::IntRect(0, 0, 0, 0));
                } else {
                    sprite_.setTextureRect(death_frames_[currentFrame_]);
                }
            }
            return;
        }

        // Normal animation
        if (frameCounter % static_cast<int>(framesPerAnimationUpdate) == 0) {
            std::vector<sf::IntRect>* frames = nullptr;

            // Select frames based on direction
            switch (currentDirection_) {
                case logic::Direction::Up: frames = &up_frames_; break;
                case logic::Direction::Down: frames = &down_frames_; break;
                case logic::Direction::Left: frames = &left_frames_; break;
                case logic::Direction::Right: frames = &right_frames_; break;
                case logic::Direction::None:
                    currentFrame_ = 0; // Mouth closed
                    frames = &right_frames_; // Use any frames
                    break;
            }

            if (frames && !frames->empty()) {
                // Simple loop: 0, 1, 2, 1, 0, 1, 2...
                if (currentDirection_ != logic::Direction::None) {
                    if (currentFrame_ == 0) currentFrame_ = 1;
                    else if (currentFrame_ == 1) currentFrame_ = 2;
                    else if (currentFrame_ == 2) currentFrame_ = 1;
                }

                // Loop back to start if somehow out of bounds
                if (currentFrame_ >= frames->size()) {
                    currentFrame_ = 0;
                }

                sprite_.setTextureRect((*frames)[currentFrame_]);
            }
        }

        // Reset frame counter periodically to prevent overflow
        if (frameCounter > 1000) frameCounter = 0;
    }

    void PacManView::onGameEvent(logic::GameEvent event, int data) {
        switch (event) {
        case logic::GameEvent::PacmanDied:
            std::cout << "PacManView: Pacman died! Starting death animation." << std::endl;
            currentDirection_ = logic::Direction::None;
            currentFrame_ = 0;
            animationTimer_ = 0.0f;
            isPlayingDeathAnimation_ = true;
            deathAnimationComplete_ = false;
            break;

        case logic::GameEvent::DirectionChanged:
            if (data >= 0 && data <= 4) {
                logic::Direction newDirection = static_cast<logic::Direction>(data);

                // Reset death animation state if we're moving again
                if (isPlayingDeathAnimation_ || deathAnimationComplete_) {
                    isPlayingDeathAnimation_ = false;
                    deathAnimationComplete_ = false;
                }

                // Only reset if direction actually changed
                if (currentDirection_ != newDirection) {
                    currentDirection_ = newDirection;
                    currentFrame_ = 0;
                    animationTimer_ = 0.0f;

                    // Immediately update to first frame
                    if (currentDirection_ != logic::Direction::None) {
                        std::vector<sf::IntRect>* frames = nullptr;
                        switch (currentDirection_) {
                            case logic::Direction::Up: frames = &up_frames_; break;
                            case logic::Direction::Down: frames = &down_frames_; break;
                            case logic::Direction::Left: frames = &left_frames_; break;
                            case logic::Direction::Right: frames = &right_frames_; break;
                        }
                        if (frames && !frames->empty()) {
                            sprite_.setTextureRect((*frames)[0]);
                        }
                    }
                }
            }
            break;

        default:
            break;
        }
    }
}