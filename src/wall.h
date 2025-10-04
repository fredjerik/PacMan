#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H
#include "entity.h"


class wall: public entity
{
public:
    wall() : entity()
    {
    }
    ~wall() override = default;
};


#endif //PACMAN_WALL_H