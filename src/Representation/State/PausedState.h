#ifndef PACMAN_PAUSEDSTATE_H
#define PACMAN_PAUSEDSTATE_H

#include "State.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace state {

    class PauseState : public State {
    public:
        explicit PauseState(StateManager* stateManager);
        void executeSelectedOption();
        void handleInput(sf::Event& event) override;
        void updateSelection();
        void update(float deltaTime) override;
        void draw() override;

    private:
        void initText();

        sf::Font font_;
        sf::Text pauseText_;
        sf::Text resumeText_;
        sf::Text quitText_;
        sf::Text instructionText_;
        sf::RectangleShape background_;

        int selectedOption_ = 0;
    };

} // namespace state


#endif //PACMAN_PAUSEDSTATE_H