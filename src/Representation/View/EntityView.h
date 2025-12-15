#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H

#include "../../Logic/Patterns/Observer.h" // Include Observer from the view directory
#include "../../Logic/Entities/Entity.h"
#include "../Camera.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace view {

    // Base class for all views. It's an Observer.
    class EntityView : public logic::Observer { // Inherit from view::Observer
    public:
        // Constructor for entities that are represented by a sprite
        EntityView(std::shared_ptr<logic::Entity> model, const sf::IntRect& textureRect);
        
        virtual ~EntityView() = default;

        // Implementation of the Observer pattern's update method
        void update() override;

        // The main game loop will call this to draw the entity
        void draw(logic::Renderer& renderer) override;

    protected:
        std::weak_ptr<logic::Entity> entity_model_;
        sf::Texture texture_;
        sf::Sprite sprite_;
        sf::IntRect textureRect_;
    };

}

#endif //PACMAN_ENTITYVIEW_H