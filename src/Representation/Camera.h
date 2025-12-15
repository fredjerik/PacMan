#ifndef PACMAN_CAMERA_H
#define PACMAN_CAMERA_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

// Forward declare Position to avoid including the whole Entity.h
namespace logic { struct Position; }

class Camera {
public:
    Camera(int gridWidth, int gridHeight, int windowWidth, int windowHeight):
    gridWidth(gridWidth), gridHeight(gridHeight), windowWidth(windowWidth), windowHeight(windowHeight) {
        updateScale(); // Calculate initial scale
    }

    // Update the camera with the window's current size
    void updateWindowSize(unsigned int width, unsigned int height);

    // Project a logical world position to a screen pixel position
    sf::Vector2f project(const logic::Position& logicalPos) const;

    // Project a logical scalar value to pixels
    float projectScalarWidth(float logicalSize) const;
    float projectScalarHeight(float logicalSize) const;

    // Get the pixel size of a single grid cell
    sf::Vector2f getCellSize() const;

    // Get the offset to center the game in the window
    sf::Vector2f getViewOffset() const;

    // Get the pixel size of the entire game area
    sf::Vector2f getGameAreaSize() const;

    // Get the rectangle of the game area in window coordinates
    sf::FloatRect getGameAreaRect() const;

    // Check if bars are on sides or top/bottom
    bool hasSideBars() const;
    bool hasTopBottomBars() const;

private:
    void updateScale(); // Recalculate scale factors

    int windowWidth;
    int windowHeight;
    int gridWidth;
    int gridHeight;

    // Scale factor (pixels per grid cell)
    float uniformScale;

    // Offsets for centering when window doesn't match grid aspect ratio
    float offsetX;
    float offsetY;
};

#endif //PACMAN_CAMERA_H