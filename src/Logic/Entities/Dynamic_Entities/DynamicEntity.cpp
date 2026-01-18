#include "DynamicEntity.h"

#include <cmath>
#include <iostream>
#include <typeinfo>
#include <string>

namespace logic {

    DynamicEntity::DynamicEntity(Position startPos, Size size, Size tile_size, float speed)
        : Entity(startPos, size, tile_size), currentDirection(Direction::None), nextDirection(Direction::None),
          speed_(speed), velX(0.0f), velY(0.0f), m_velX_unit(tile_size.width), m_velY_unit(tile_size.height)
    {
    }

    void DynamicEntity::setDirection(Direction dir) {
        if (currentDirection != dir)
        {
            OnEvent(GameEvent::DirectionChanged, static_cast<int>(dir));
        }
        currentDirection = dir;
        switch (currentDirection) {
            case Direction::None:
                velX = 0;
                velY = 0;
                break;
            case Direction::Up:
                velX = 0;
                velY = -m_velY_unit;
                break;
            case Direction::Down:
                velX = 0;
                velY = m_velY_unit;
                break;
            case Direction::Left:
                velX = -m_velX_unit;
                velY = 0;
                break;
            case Direction::Right:
                velX = m_velX_unit;
                velY = 0;
                break;
        }

    }

    void DynamicEntity::setNextDirection(Direction& dir) {
        nextDirection = dir;
    }

    void DynamicEntity::setPosition(Position& pos)
    {
        pos_ = pos;
    }

    Direction DynamicEntity::getDirection() const {
        return currentDirection;
    }

    Direction DynamicEntity::getNextDirection() const
    {
        return nextDirection;
    }

    float DynamicEntity::getSpeed() const {
        return speed_;
    }

    void DynamicEntity::update(float deltaTime) {
        pos_.x += velX * speed_ * deltaTime;
        pos_.y += velY * speed_ * deltaTime;
        notify();
    }

    Position DynamicEntity::getProposedPosition(float deltaTime, Direction dir) const {
        float tempVelX = 0;
        float tempVelY = 0;
        switch (dir) {
            case Direction::None:
                break;
            case Direction::Up:
                tempVelY = -m_velY_unit;
                break;
            case Direction::Down:
                tempVelY = m_velY_unit;
                break;
            case Direction::Left:
                tempVelX = -m_velX_unit;
                break;
            case Direction::Right:
                tempVelX = m_velX_unit;
                break;
        }
        Position proposed = pos_;
        proposed.x += tempVelX * speed_ * deltaTime;
        proposed.y += tempVelY * speed_ * deltaTime;
        return proposed;
    }

    Direction DynamicEntity::getReverseDirection(Direction currentDir)
    {
        switch (currentDir)
        {
        case Direction::Left: return Direction::Right;
        case Direction::Right: return Direction::Left;
        case Direction::Up: return Direction::Down;
        case Direction::Down: return Direction::Up;
        default: return Direction::None;
        }
    }

    bool DynamicEntity::isReverseDirection(Direction dir1, Direction dir2) {
        return (dir1 == Direction::Left && dir2 == Direction::Right) ||
               (dir1 == Direction::Right && dir2 == Direction::Left) ||
               (dir1 == Direction::Up && dir2 == Direction::Down) ||
               (dir1 == Direction::Down && dir2 == Direction::Up);
    }

    void DynamicEntity::snapToGrid(float tileWidth, float tileHeight) {
        float xInGrid = (pos_.x + 1.0f) / tileWidth;
        float tileX = std::round(xInGrid);
        pos_.x = tileX * tileWidth - 1.0f;

        float yInGrid = (pos_.y + 1.0f) / tileHeight;
        float tileY = std::round(yInGrid);
        pos_.y = tileY * tileHeight - 1.0f;

        notify();
    }
} // namespace logic