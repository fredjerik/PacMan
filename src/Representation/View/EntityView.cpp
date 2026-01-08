#include "EntityView.h"
#include "SFMLRenderer.h"
#include "../../Singleton/RenderWindow.h"
#include <iostream>

namespace view {

EntityView::EntityView(std::weak_ptr<logic::Entity> model, const sf::IntRect& textureRect)
    : entity_model_(model), textureRect_(textureRect) {

    if (!texture_.loadFromFile("textures/sprite.png")) {
        std::cerr << "Failed to load sprite sheet!" << std::endl;
    }

    sprite_.setTexture(texture_);

    sprite_.setTextureRect(textureRect_);
}

void EntityView::update() {
    if (auto model = entity_model_.lock()) {
    }
}

void EntityView::draw(logic::Renderer& renderer) {
    if (auto model = entity_model_.lock()) {
        updateAnimation();
        auto& sfmlRenderer = static_cast<representation::SFMLRenderer&>(renderer);

        Camera& camera = sfmlRenderer.getCamera();
        sf::RenderWindow& window = singleton::RenderWindow::getInstance(); // Assuming singleton

        logic::Position logicalPos = model->getPosition();

        sf::Vector2f screenPos = camera.project(logicalPos);

        if (textureRect_.width > 0 && textureRect_.height > 0) {
            float scaleX = camera.getCellSize().x * model->getSize().width / textureRect_.width;
            float scaleY = camera.getCellSize().y * model->getSize().height / textureRect_.height;
            sprite_.setScale(scaleX, scaleY);
        }

        float offsetX = (camera.getCellSize().x * (1.0f - model->getSize().width)) / 2.0f;
        float offsetY = (camera.getCellSize().y * (1.0f - model->getSize().height)) / 2.0f;

        sprite_.setPosition(screenPos.x + offsetX, screenPos.y + offsetY);

        window.draw(sprite_);

    }
}

} // namespace view
