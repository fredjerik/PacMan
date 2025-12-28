#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "../Camera.h"
#include "../../Logic/World.h"
#include "../FactorySFML.h" // Include the concrete factory
#include <vector>
#include <memory>

// Forward declarations
namespace state { class StateManager; }

namespace state {

    class LevelState : public State {
    public:
        explicit LevelState(StateManager* stateManager);
        ~LevelState() override = default;

        void handleInput(sf::Event& event) override;
        void update(float deltaTime) override;
        void draw() override;

    private:
        std::unique_ptr<Camera> m_camera;
        std::unique_ptr<logic::World> m_world;
        std::unique_ptr<factory::FactorySFML> m_factory; // LevelState owns the factory
        std::shared_ptr<logic::Score> m_score;

        sf::View m_gameView;
        sf::View m_uiView;
        sf::Font m_font;
    };

} // state

#endif //PACMAN_LEVELSTATE_H
