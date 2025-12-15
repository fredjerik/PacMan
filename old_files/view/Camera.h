#ifndef PACMAN_CAMERA_H
#define PACMAN_CAMERA_H

#include <SFML/System/Vector2.hpp>
#include "../Logic/Entities/Entity.h"

namespace view {

    class Camera {
    public:
        // Constructor takes the size of the world grid
        explicit Camera(sf::Vector2u worldGridSize);

        // Projects a position from world grid coordinates to screen pixel coordinates, assuming the worldPos is the center of the object
        sf::Vector2f projectCenter(logic::Position worldPos) const;

        // Projects a position from world floating-point coordinates to screen pixel coordinates, assuming the worldPos is the top-left of the object
        sf::Vector2f projectTopLeft(logic::Position worldPos) const;

        // Projects a scalar value (like a radius) from world grid units to pixels
        float projectScalar(float worldSize) const;

    private:
        float scale_;
        float offsetX_;
        float offsetY_;
    };

}

#endif //PACMAN_CAMERA_H

