#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "dynamic_entity.h"

class pacman: public dynamic_entity
{
public:
    pacman(): dynamic_entity()
    {
        texture_.loadFromFile("../textures/sprite.png");
        speed = 200.0f;
        pacman::set_rectangle(direction::None);
    }
    void set_rectangle(direction dir) override;
};


#endif //PACMAN_PACMAN_H