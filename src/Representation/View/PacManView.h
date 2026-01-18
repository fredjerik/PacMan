#ifndef PACMAN_PACMANVIEW_H
#define PACMAN_PACMANVIEW_H

#include "EntityView.h"
#include <memory>
#include "Logic/Entities/Dynamic_Entities/PacmanEntity.h"

namespace logic { class Entity; }

namespace view
{
    class PacManView : public EntityView {
    public:
        explicit PacManView(std::weak_ptr<logic::PacmanEntity> model);
        void onGameEvent(logic::GameEvent event, int data) override;
        void updateAnimation() override;

    private:
        std::vector<sf::IntRect> up_frames_;
        std::vector<sf::IntRect> down_frames_;
        std::vector<sf::IntRect> left_frames_;
        std::vector<sf::IntRect> right_frames_;
        std::vector<sf::IntRect> death_frames_;

        logic::Direction currentDirection_ = logic::Direction::None;
        float animationTimer_ = 0.0f;
        int currentFrame_ = 0;
        float frameDuration_ = 0.1f;
        float deathFrameDuration_;

        bool isPlayingDeathAnimation_ = false;
        bool deathAnimationComplete_ = false;
    };
} // view

#endif //PACMAN_PACMANVIEW_H