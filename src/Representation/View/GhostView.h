#ifndef PACMAN_GHOSTVIEW_H
#define PACMAN_GHOSTVIEW_H
#include "EntityView.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Logic/Entities/Dynamic_Entities/GhostEntity.h"

namespace view
{
    class GhostView : public EntityView {
    public:
        explicit GhostView(std::weak_ptr<logic::GhostEntity> model,
                          int normalSpriteX, int normalSpriteY);

        void onGameEvent(logic::GameEvent event, int data) override;
        void updateAnimation() override;

    protected:
        std::array<std::array<std::vector<sf::IntRect>, 4>, 4> frames_;

        logic::Direction currentDirection_ = logic::Direction::Left;
        int currentMode_ = 0; // 0=normal, 1=fear, 2=fear flashing, 3=eaten
        int currentFrame_ = 0;
        float animationTimer_ = 0.0f;
        float frameDuration_ = 0.15f;

        void setupFrames(int normalSpriteX, int normalSpriteY);
    };

    class BlinkyView : public GhostView {
    public:
        explicit BlinkyView(std::weak_ptr<logic::BlinkyEntity> model);
    };

    class PinkyView : public GhostView {
    public:
        explicit PinkyView(std::weak_ptr<logic::PinkyEntity> model);
    };

    class InkyView : public GhostView {
    public:
        explicit InkyView(std::weak_ptr<logic::InkyEntity> model);
    };

    class ClydeView : public GhostView {
    public:
        explicit ClydeView(std::weak_ptr<logic::ClydeEntity> model);
    };

} // view

#endif //PACMAN_GHOSTVIEW_H