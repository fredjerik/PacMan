#ifndef PACMAN_DYNAMIC_ENTITY_H
#define PACMAN_DYNAMIC_ENTITY_H
#include "entity.h"

enum class direction { None, Up, Down, Left, Right };

struct velocity
{
    float x = 0;
    float y = 0;
};

class dynamic_entity: public entity
{
public:
    dynamic_entity() = default;
    void update(float& delta_time);
    void set_direction(direction dir);
    virtual void set_rectangle(direction dir) = 0;
protected:
    direction direction_;
    velocity velocity_;
    float speed;
};


#endif //PACMAN_MOVING_ENTITY_H