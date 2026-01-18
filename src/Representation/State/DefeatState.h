#ifndef PACMAN_DEFEATSTATE_H
#define PACMAN_DEFEATSTATE_H

#include "State.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace state {

    class DefeatState : public State {
    public:
        DefeatState(StateManager* stateManager, int score, int level);
        void handleInput(sf::Event& event) override;
        void update(float deltaTime) override {}
        void draw() override;

    private:
        void initText();

        int score_;
        int level_;

        sf::Font font_;
        sf::Text defeatText_;
        sf::Text scoreText_;
        sf::Text levelText_;
        sf::Text instructionText_;
        sf::RectangleShape background_;
    };

} // state

#endif //PACMAN_DEFEATSTATE_H