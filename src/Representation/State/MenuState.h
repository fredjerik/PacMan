#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H

#include "State.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace state {

    class MenuState : public State {
    public:
        explicit MenuState(StateManager* stateManager);
        void handleInput(sf::Event& event) override;
        void update(float deltaTime) override;
        void draw() override;

    private:
        void initText();

        sf::Font font_;
        sf::Text titleText_;
        sf::Text startText_;
        sf::Text quitText_;
        sf::Text instructionText_;

        int selectedOption_ = 0; // 0 = Start, 1 = Quit
    };

} // namespace state


#endif //PACMAN_MENUSTATE_H
