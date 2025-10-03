#include "pacman.h"

void pacman::set_rectangle(direction dir)
{
    switch (dir)
    {
        case direction::Up: rectangle_ = {850, 500, 50, 50};
        case direction::Down: rectangle_ = {850, 350, 50, 50};
        case direction::Left: rectangle_ = {850, 500, 50, 50};
        case direction::Right: rectangle_ = {850, 50, 50, 50};
        default: rectangle_ = {850, 0, 50, 50};
        sprite_.setTexture(texture_);
        sprite_.setTextureRect(rectangle_);
    }
}