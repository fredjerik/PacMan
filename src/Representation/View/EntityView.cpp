#include "EntityView.h"
#include "SFMLRenderer.h"
#include "../../Singleton/RenderWindow.h" // Assuming this is the name of the singleton header
#include <iostream>

namespace view {

EntityView::EntityView(std::shared_ptr<logic::Entity> model, const sf::IntRect& textureRect)
    : entity_model_(model) {

    // Load the texture from the sprite sheet file
    if (!texture_.loadFromFile("/home/frederik/Projects/PacMan/textures/sprite.png")) {
        // It's good practice to handle potential loading errors
        std::cerr << "Failed to load sprite sheet!" << std::endl;
    }

    // Set the texture for the sprite
    sprite_.setTexture(texture_);

    // Set the part of the texture to be displayed
    sprite_.setTextureRect(textureRect);

    // Set the origin to the center of the sprite
    // sprite_.setOrigin(textureRect.width / 2.0f, textureRect.height / 2.0f);

    // The update() method is no longer strictly necessary to call here,
    // as all position calculation is done in draw().
    // However, it does no harm.
    update();
}

void EntityView::update() {
    // This method is called by the model when its state changes.
    // For now, we don't need to do anything here, but it could be used
    // for animation logic in the future.
    if (auto model = entity_model_.lock()) {
        // The old implementation stored the logical position here.
        // We can now get it directly in the draw call.
    }
}

void EntityView::draw(logic::Renderer& renderer) {
    // The model is weak_ptr, so we must lock it to get a shared_ptr
    if (auto model = entity_model_.lock()) {
        // 1. Cast the generic renderer to the concrete SFMLRenderer
        auto& sfmlRenderer = static_cast<representation::SFMLRenderer&>(renderer);
        
        // 2. Get the tools from the renderer and the singleton
        Camera& camera = sfmlRenderer.getCamera();
        sf::RenderWindow& window = singleton::RenderWindow::getInstance(); // Assuming singleton

        // 3. Get logical data from the model
        logic::Position logicalPos = model->getPosition();
        float logicalWidth = model->getSize().width;
        float logicalHeight = model->getSize().height;

        // 4. Use the camera to project logic to pixels
        sf::Vector2f screenPos = camera.project(logicalPos);
        float desiredPixelWidth = camera.projectScalarWidth(logicalWidth);
        float desiredPixelHeight = camera.projectScalarHeight(logicalHeight);

        // 5. Set scale and position for the sprite
        float currentSize = sprite_.getLocalBounds().width;
        if (currentSize != 0) {
            float pixelWidth = desiredPixelWidth / currentSize;
            float pixelHeight = desiredPixelHeight / currentSize;
            sprite_.setScale(pixelWidth, pixelHeight);
        }
        sprite_.setPosition(screenPos);

        // 6. Draw the sprite
        window.draw(sprite_);
    }
}

} // namespace view
