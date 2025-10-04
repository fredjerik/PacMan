#ifndef PACMAN_CONSUMABLE_H
#define PACMAN_CONSUMABLE_H
#include "entity.h"


class consumable: public entity
{
public:
    consumable() : entity()
    {
    }
    ~consumable() override = default;
};


#endif //PACMAN_CONSUMABLE_H