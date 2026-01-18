#include "Score.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Singleton/RenderWindow.h"

namespace logic
{
    void Score::draw(Renderer& renderer) {
        sf::RenderWindow& window = singleton::RenderWindow::getInstance();

        static sf::Font font;
        static bool fontLoaded = false;

        if (!fontLoaded) {
            if (!font.loadFromFile("fonts/Pokemon.ttf")) {
                std::cerr << "Failed to load font in Score::draw()" << std::endl;
                return;
            }
            fontLoaded = true;
        }

        sf::Text scoreText;
        scoreText.setCharacterSize(30);
        scoreText.setFont(font);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(50.0f, 100.0f);
        scoreText.setString("World Record: " + std::to_string(global_highscore));
        window.draw(scoreText);

        scoreText.setPosition(50.0f, 140.0f);
        scoreText.setString("Personal Best: " + std::to_string(personal_best));
        window.draw(scoreText);

        scoreText.setPosition(50.0f, 180.0f);
        scoreText.setString("Score: " + std::to_string(current_score));
        window.draw(scoreText);

        scoreText.setPosition(50.0f, 220.0f);
        scoreText.setString("PacMan Lives: ");
        window.draw(scoreText);

        static sf::Texture texture;
        static bool textureLoaded = false;

        if (!textureLoaded) {
            if (!texture.loadFromFile("textures/sprite.png")) {
                std::cerr << "Failed to load texture in Score::draw()" << std::endl;
                return;
            }
            textureLoaded = true;
        }

        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(852, 54, 35, 35));


        for (int i = 0; i < pacman_lives; i++) {
            constexpr float spacing = 40.0f;
            constexpr float startY = 220.0f;
            constexpr float startX = 270.0f;
            sprite.setPosition(startX + i * spacing, startY);
            window.draw(sprite);
        }
    }
} // logic