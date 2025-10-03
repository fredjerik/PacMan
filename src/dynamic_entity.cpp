#include "dynamic_entity.h"

void dynamic_entity::set_direction(direction dir)
{
    switch(dir) {
    case direction::Up:    velocity_ = {0, -speed}; set_rectangle(direction::Up); break;
    case direction::Down:  velocity_ = {0, speed}; set_rectangle(direction::Down); break;
    case direction::Left:  velocity_ = {-speed, 0}; set_rectangle(direction::Left); break;
    case direction::Right: velocity_ = {speed, 0}; set_rectangle(direction::Right); break;
    case direction::None:  velocity_ = {0, 0}; set_rectangle(direction::None); break;
    }
}

void dynamic_entity::update(float& delta_time)
{
    position_.x += velocity_.x * delta_time;
    position_.y += velocity_.y * delta_time;
    sprite_.setPosition(position_.x, position_.y);
}

