#include "Camera.h"
#include "Logic/Entities/Entity.h"
#include <algorithm>

void Camera::updateScale() {
    // Calculate maximum scale that fits within window
    float maxScaleForWidth = static_cast<float>(windowWidth) / static_cast<float>(gridWidth);
    float maxScaleForHeight = static_cast<float>(windowHeight) / static_cast<float>(gridHeight);

    // Use the smaller scale to ensure it fits both dimensions
    uniformScale = std::min(maxScaleForWidth, maxScaleForHeight);

    // Calculate pixel dimensions with chosen scale
    float gridPixelWidth = gridWidth * uniformScale;
    float gridPixelHeight = gridHeight * uniformScale;

    // Center in window
    offsetX = (windowWidth - gridPixelWidth) / 2.0f;
    offsetY = (windowHeight - gridPixelHeight) / 2.0f;
}

void Camera::updateWindowSize(unsigned int width, unsigned int height) {
    windowWidth = width;
    windowHeight = height;
    updateScale();
}

sf::Vector2f Camera::project(const logic::Position& logicalPos) const {
    // Convert from [-1, 1] logical space to [0, 1] normalized space
    float normalizedX = (logicalPos.x + 1.0f) / 2.0f;
    float normalizedY = (logicalPos.y + 1.0f) / 2.0f;

    // Map to grid coordinates
    float gridX = normalizedX * gridWidth;
    float gridY = normalizedY * gridHeight;

    // Convert to pixel coordinates
    float pixelX = gridX * uniformScale + offsetX;
    float pixelY = gridY * uniformScale + offsetY;

    return {pixelX, pixelY};
}

float Camera::projectScalarWidth(float logicalSize) const {
    float gridUnits = logicalSize / 2.0f * gridWidth;
    return gridUnits * uniformScale;
}

float Camera::projectScalarHeight(float logicalSize) const {
    float gridUnits = logicalSize / 2.0f * gridHeight;
    return gridUnits * uniformScale;
}

sf::Vector2f Camera::getCellSize() const {
    return {uniformScale, uniformScale};
}

sf::Vector2f Camera::getViewOffset() const {
    return {offsetX, offsetY};
}

sf::Vector2f Camera::getGameAreaSize() const {
    return {gridWidth * uniformScale, gridHeight * uniformScale};
}

sf::FloatRect Camera::getGameAreaRect() const {
    return {offsetX, offsetY, gridWidth * uniformScale, gridHeight * uniformScale};
}

bool Camera::hasSideBars() const {
    return offsetX > 0;
}

bool Camera::hasTopBottomBars() const {
    return offsetY > 0;
}