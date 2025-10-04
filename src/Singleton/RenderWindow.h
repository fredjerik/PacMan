#ifndef PACMAN_RENDERWINDOW_H
#define PACMAN_RENDERWINDOW_H

#include <SFML/Graphics.hpp>
namespace singleton
{
    class RenderWindow {
    public:
        static sf::RenderWindow& getInstance();

        // Delete copy constructor and assignment operator to prevent copying
        RenderWindow(const RenderWindow&) = delete;
        RenderWindow& operator=(const RenderWindow&) = delete;

    private:
        RenderWindow(); // Private constructor to prevent direct instantiation
        static sf::RenderWindow* windowInstance;
    };
}

#endif //PACMAN_RENDERWINDOW_H
