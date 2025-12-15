#include "EntityView.h"
#include <iostream>

namespace view {

EntityView::EntityView(std::shared_ptr<logic::Entity> model, const Camera& camera, const sf::IntRect& textureRect)
    : entity_model_(model), camera_(camera) {

    // Load the texture from the sprite sheet file
    if (!texture_.loadFromFile("/home/frederik/Projects/PacManOld/textures/sprite.png")) {
        // It's good practice to handle potential loading errors
        std::cerr << "Failed to load sprite sheet!" << std::endl;
    }

    // Set the texture for the sprite
    sprite_.setTexture(texture_);

    // Set the part of the texture to be displayed
    sprite_.setTextureRect(textureRect);

    // Set the origin to the center of the sprite
    sprite_.setOrigin(textureRect.width / 2.0f, textureRect.height / 2.0f);

    // Calculate the scale needed to make the sprite fit the tile size
    float desiredSize = camera_.projectScalar(1.0f); // The sprite should be one tile wide
    float currentSize = sprite_.getLocalBounds().width;
    if (currentSize != 0) {
        float scale = desiredSize / currentSize;
        sprite_.setScale(scale, scale);
    }

    update();
}

void EntityView::update() {
    if (auto model = entity_model_.lock()) {
        // Get model position (in grid coordinates)
        logic::Position modelPos = model->getPosition();

        // Use the camera to project the world position to a screen position
        sprite_.setPosition(camera_.projectCenter(modelPos));
    }
}

void EntityView::draw(sf::RenderWindow& window) {
    window.draw(sprite_);
}

} // namespace view
