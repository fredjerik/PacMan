#ifndef PACMAN_DYNAMICENTITY_H
#define PACMAN_DYNAMICENTITY_H

#include "../Entity.h"

namespace logic {

    enum class Direction { None, Up, Down, Left, Right };

    class DynamicEntity : public Entity {
    public:
        explicit DynamicEntity(Position startPos, Size size, float velX_unit, float velY_unit);

        void update(float deltaTime) override;

        Position getProposedPosition(float deltaTime, Direction dir) const;
        void snapToGrid(float tileWidth, float tileHeight);

        void setDirection(Direction dir);
        void setNextDirection(Direction& dir);
        void setPosition(Position& pos_);
        Direction getDirection() const;
        Direction getNextDirection() const;
        float getSpeed() const;
        void set_speed(float speed_) {speed = speed_;}
        void clearNextDirection() {nextDirection = Direction::None;}

    protected:
        Direction currentDirection;
        Direction nextDirection;
        float speed;
        float velX;
        float velY;
        float m_velX_unit;
        float m_velY_unit;
        static int frameCounter;
    };

} // namespace Logic

#endif //PACMAN_DYNAMICENTITY_H

