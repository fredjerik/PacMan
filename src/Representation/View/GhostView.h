#ifndef PACMAN_GHOSTVIEW_H
#define PACMAN_GHOSTVIEW_H
#include "EntityView.h"
#include <SFML/Graphics.hpp>
#include <vector>
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
        // Normal mode frames (colored ghost)
        std::vector<sf::IntRect> normalUpFrames;
        std::vector<sf::IntRect> normalLeftFrames;
        std::vector<sf::IntRect> normalDownFrames;
        std::vector<sf::IntRect> normalRightFrames;

        // Fear mode frames (solid blue)
        std::vector<sf::IntRect> fearFrames;

        // Fear flashing mode frames (blue/white alternating)
        std::vector<sf::IntRect> fearFlashingFrames;

        // Eaten mode frames (just eyes)
        std::vector<sf::IntRect> eatenUpFrames;
        std::vector<sf::IntRect> eatenLeftFrames;
        std::vector<sf::IntRect> eatenDownFrames;
        std::vector<sf::IntRect> eatenRightFrames;

        logic::Direction currentDirection_ = logic::Direction::Left;
        int currentMode_ = 0; // 0=normal, 1=fear, 2=fear flashing, 3=eaten
        int currentFrame_ = 0;
        int frameCounter_ = 0;

        void setupFrames(int normalSpriteX, int normalSpriteY);
        const std::vector<sf::IntRect>& getCurrentFrames() const;
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