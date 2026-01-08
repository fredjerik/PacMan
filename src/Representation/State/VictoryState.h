#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H

#include "State.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace state {

    class VictoryState : public State {
    public:
        VictoryState(StateManager* stateManager, int score, int level);
        void handleInput(sf::Event& event) override;
        void update(float deltaTime) override;
        void draw() override;

    private:
        void initText();

        int score_;
        int level_;

        sf::Font font_;
        sf::Text victoryText_;
        sf::Text scoreText_;
        sf::Text levelText_;
        sf::Text instructionText_;
        sf::RectangleShape background_;
    };

} // namespace state

#endif // PACMAN_VICTORYSTATE_H