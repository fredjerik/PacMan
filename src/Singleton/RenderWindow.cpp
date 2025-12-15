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
            windowInstance = new sf::RenderWindow({800, 1080}, "Pac-Man", sf::Style::Fullscreen);  //running
            // windowInstance = new sf::RenderWindow({800, 1080}, "Pac-Man"); //for debugging
            windowInstance->setFramerateLimit(60);
        }
        return *windowInstance;
    }
}