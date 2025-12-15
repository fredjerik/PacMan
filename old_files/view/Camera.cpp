#include "Camera.h"
#include <algorithm> // For std::min
#include "../Singleton/RenderWindow.h"
using namespace singleton;

namespace view {

    Camera::Camera(sf::Vector2u worldGridSize) { // Removed windowSize parameter
        sf::Vector2u windowSize = RenderWindow::getInstance().getSize(); // Get window size from Singleton
        if (worldGridSize.x == 0 || worldGridSize.y == 0) {
            scale_ = 0;
            offsetX_ = 0;
            offsetY_ = 0;
            return;
        }

        // Calculate the scale factor for both axes
        float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(worldGridSize.x);
        float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(worldGridSize.y);

        // Use the smaller scale factor to maintain aspect ratio
        scale_ = std::min(scaleX, scaleY);

        // Calculate the total size of the map in pixels
        float mapPixelWidth = static_cast<float>(worldGridSize.x) * scale_;
        float mapPixelHeight = static_cast<float>(worldGridSize.y) * scale_;

        // Calculate the offset to center the map
        offsetX_ = (static_cast<float>(windowSize.x) - mapPixelWidth) / 2.0f;
        offsetY_ = (static_cast<float>(windowSize.y) - mapPixelHeight) / 2.0f;
    }

    sf::Vector2f Camera::projectCenter(logic::Position worldPos) const {
        // We add 0.5f to center the entity in the middle of the tile
        float pixelX = (worldPos.x + 0.5) * scale_ + offsetX_;
        float pixelY = (worldPos.y + 0.5f) * scale_ + offsetY_;
        return {pixelX, pixelY};
    }

    float Camera::projectScalar(float worldSize) const {
        return worldSize * scale_;
    }

    sf::Vector2f Camera::projectTopLeft(logic::Position worldPos) const {
        float pixelX = worldPos.x * scale_ + offsetX_;
        float pixelY = worldPos.y * scale_ + offsetY_;
        return {pixelX, pixelY};
    }

}
