#include <SFML/Graphics.hpp>
#include "pacman.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1800, 1000}), "Pac-Man Sprite Test");
    pacman pacman;
    sf::Clock clock;

    while (window.isOpen())
    {
        float delta_time = clock.restart().asSeconds(); // Move this HERE

        // Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Real-time input handling (OUTSIDE event loop)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            pacman.set_direction(direction::Up);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            pacman.set_direction(direction::Down);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            pacman.set_direction(direction::Left);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            pacman.set_direction(direction::Right);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        // Update and render (OUTSIDE event loop)
        pacman.update(delta_time);

        window.clear();
        window.draw(pacman.get_sprite());
        window.display();
    }
    return 0;
}