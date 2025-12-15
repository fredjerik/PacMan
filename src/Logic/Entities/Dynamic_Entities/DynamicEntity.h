#ifndef PACMAN_DYNAMICENTITY_H
#define PACMAN_DYNAMICENTITY_H

#include "../Entity.h"

namespace logic {

    // Enum for movement direction
    enum class Direction { None, Up, Down, Left, Right };

    class DynamicEntity : public Entity {
    public:
        explicit DynamicEntity(Position startPos, Size size, float velX_unit, float velY_unit);

        void update(float deltaTime) override;

        Position getProposedPosition(float deltaTime, Direction dir) const;
        void revertPosition();

        void setDirection(Direction dir);
        Direction getDirection() const;
        float getSpeed() const;
        void set_speed(float speed_) {speed = speed_;}

    protected:
        Direction currentDirection;
        float speed; // Default speed
        float velX; // Current velocity component
        float velY; // Current velocity component
        float m_velX_unit; // Unit velocity for X-axis movement
        float m_velY_unit; // Unit velocity for Y-axis movement
        Position previousPosition;
    };

} // namespace Logic

#endif //PACMAN_DYNAMICENTITY_H

