#include "DynamicEntity.h"

namespace logic {

    DynamicEntity::DynamicEntity(Position startPos, Size size,float velX_unit, float velY_unit)
        : Entity(startPos, size),  currentDirection(Direction::None), speed(1.0f),
          velX(0.0f), velY(0.0f), m_velX_unit(velX_unit), m_velY_unit(velY_unit),
          previousPosition(startPos) {}

    void DynamicEntity::setDirection(Direction dir) {
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

    Direction DynamicEntity::getDirection() const {
        return currentDirection;
    }

    float DynamicEntity::getSpeed() const {
        return speed;
    }

    void DynamicEntity::update(float deltaTime) {
        previousPosition = pos;
        pos.x += velX * speed * deltaTime;
        pos.y += velY * speed * deltaTime;
        notify();
    }

    void DynamicEntity::revertPosition() {
        pos = previousPosition;
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
        Position proposed = pos;
        proposed.x += tempVelX * speed * deltaTime;
        proposed.y += tempVelY * speed * deltaTime;
        return proposed;
    }

} // namespace logic