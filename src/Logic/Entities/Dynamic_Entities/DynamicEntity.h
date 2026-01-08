#ifndef PACMAN_DYNAMICENTITY_H
#define PACMAN_DYNAMICENTITY_H

#include "../Entity.h"
#include <string>
namespace logic {

    enum class Direction
    {
        None, Up, Down, Left, Right
    };



    class DynamicEntity : public Entity {
    public:
        // static std::string to_string(Direction dir)
        // {
        //     switch (dir)
        //     {
        //     case Direction::Up:
        //         return "Up";
        //     case Direction::Down:
        //         return "Down";
        //     case Direction::Left:
        //         return "Left";
        //     case Direction::Right:
        //         return "Right";
        //     case Direction::None:
        //         return "None";
        //     }
        //     return "error";
        // }

        explicit DynamicEntity(Position startPos, Size size, float velX_unit, float velY_unit, float speed);

        void update(float deltaTime) override;

        Position getProposedPosition(float deltaTime, Direction dir) const;
        void snapToGrid(float tileWidth, float tileHeight);

        void setDirection(Direction dir);
        void setNextDirection(Direction& dir);
        void setPosition(Position& pos_);
        Direction getDirection() const;
        Direction getNextDirection() const;
        float getSpeed() const;
        void set_speed(float speed) {speed_ = speed;}
        void clearNextDirection() {nextDirection = Direction::None;}
        virtual void reset() = 0;

    protected:
        Direction currentDirection;
        Direction nextDirection;
        float speed_;
        float velX;
        float velY;
        float m_velX_unit;
        float m_velY_unit;
    };

} // namespace Logic

#endif //PACMAN_DYNAMICENTITY_H

