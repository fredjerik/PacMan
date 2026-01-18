#ifndef PACMAN_DYNAMICENTITY_H
#define PACMAN_DYNAMICENTITY_H

#include "../Entity.h"
#include <string>
namespace logic {

    enum class Direction
    {
        None, Up, Down, Left, Right
    };

    static std::string dir_to_string(Direction dir)
    {
        switch (dir)
        {
        case Direction::Up:
            return "Up";
        case Direction::Down:
            return "Down";
        case Direction::Left:
            return "Left";
        case Direction::Right:
            return "Right";
        case Direction::None:
            return "None";
        }
        return "error";
    }

    class DynamicEntity : public Entity {
    public:
        explicit DynamicEntity(Position startPos, Size size, Size tile_size, float speed);

        void update(float deltaTime) override;

        Position getProposedPosition(float deltaTime, Direction dir) const;
        void snapToGrid(float tileWidth, float tileHeight);

        static Direction getReverseDirection(Direction dir1);
        static bool isReverseDirection(Direction dir1, Direction dir2);
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

