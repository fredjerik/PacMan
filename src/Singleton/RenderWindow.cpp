#include "RenderWindow.h"
namespace singleton
{
    // Initialize the static member to nullptr
    sf::RenderWindow* RenderWindow::windowInstance = nullptr;

    RenderWindow::RenderWindow() {
        // Private constructor, not meant to be called directly
    }

    sf::RenderWindow& RenderWindow::getInstance() {
        if (windowInstance == nullptr) {
            windowInstance = new sf::RenderWindow({1800, 1000}, "Pac-Man");
            windowInstance->setFramerateLimit(60);
        }
        return *windowInstance;
    }
}