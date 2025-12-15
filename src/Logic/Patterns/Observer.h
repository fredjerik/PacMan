#ifndef PACMAN_OBSERVER_H
#define PACMAN_OBSERVER_H

#include "Renderer.h"

namespace logic
{
    class Observer
    {
    public:
        virtual ~Observer() = default;
        virtual void update() = 0;
        virtual void draw(Renderer& renderer) = 0;
    };
} // logic

#endif //PACMAN_OBSERVER_H