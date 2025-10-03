#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H

#include <SFML/Graphics.hpp>

struct position {
    float x = 0;
    float y = 0;
};

class entity {
public:
    entity() = default;
    virtual ~entity() = default;
    void set_position(const position& pos) {
        position_ = pos;
        sprite_.setPosition(pos.x, pos.y);
    }

    position get_position() const { return position_; }

    sf::Sprite& get_sprite() { return sprite_; }

    void set_sprite() {
        sprite_.setTexture(texture_);
    }

protected:
    position position_;
    sf::Texture texture_;
    sf::Sprite sprite_;
    sf::IntRect rectangle_;
};

#endif