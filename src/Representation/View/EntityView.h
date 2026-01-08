#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H

#include "../../Logic/Patterns/Observer.h" // Include Observer from the view directory
#include "../../Logic/Entities/Entity.h"
#include "../Camera.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace view {

    class EntityView : public logic::Observer {
    public:
        // Constructor for entities that are represented by a sprite
        EntityView(std::weak_ptr<logic::Entity> model, const sf::IntRect& textureRect);

        virtual ~EntityView() = default;

        void update() override;
        void onGameEvent(logic::GameEvent event, int data) override = 0;
        void draw(logic::Renderer& renderer) override;

    protected:
        virtual void updateAnimation() {}
        std::weak_ptr<logic::Entity> entity_model_;
        sf::Texture texture_;
        sf::Sprite sprite_;
        sf::IntRect textureRect_;
    };
}

#endif //PACMAN_ENTITYVIEW_H