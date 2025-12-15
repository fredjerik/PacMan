#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H

#include "Observer.h" // Include Observer from the view directory
#include "../../Logic/Entities/Entity.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <memory>


namespace view {

    // Base class for all views. It's an Observer.
    class EntityView : public Observer { // Inherit from view::Observer
    public:
        // Constructor for entities that are represented by a sprite
        EntityView(std::shared_ptr<logic::Entity> model, const Camera& camera, const sf::IntRect& textureRect);
        
        virtual ~EntityView() = default;

        // Implementation of the Observer pattern's update method
        void update() override;

        // The main game loop will call this to draw the entity
        virtual void draw(sf::RenderWindow& window);

    protected:
        std::weak_ptr<logic::Entity> entity_model_;
        Camera* camera_;
        sf::Texture texture_;
        sf::Sprite sprite_;
    };

}

#endif //PACMAN_ENTITYVIEW_H