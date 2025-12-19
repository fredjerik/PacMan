#include "DynamicEntity.h"

#include <cmath>
#include <typeinfo>
#include <string>

namespace logic {

    int DynamicEntity::frameCounter = 0;

    DynamicEntity::DynamicEntity(Position startPos, float velX_unit, float velY_unit)
        : Entity(startPos),  currentDirection(Direction::None), speed(1.0f),
          velX(0.0f), velY(0.0f), m_velX_unit(velX_unit), m_velY_unit(velY_unit){}

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
    void DynamicEntity::setNextDirection(Direction& dir) {
        nextDirection = dir;
    }

    void DynamicEntity::setPosition(Position& pos_)
    {
        pos = pos_;
    }

    Direction DynamicEntity::getDirection() const {
        return currentDirection;
    }

    Direction DynamicEntity::getNextDirection() const
    {
        return nextDirection;
    }

    float DynamicEntity::getSpeed() const {
        return speed;
    }

    void DynamicEntity::update(float deltaTime) {
        pos.x += velX * speed * deltaTime;
        pos.y += velY * speed * deltaTime;

        frameCounter++;
        if (frameCounter % 12 == 0) {
            std::string typeName = typeid(*this).name();
            if (typeName.find("Pacman") != std::string::npos) {
                // std::cout << "Pacman position: (" << pos.x << ", " << pos.y << ")" << std::endl;
            }
        }

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
        Position proposed = pos;
        proposed.x += tempVelX * speed * deltaTime;
        proposed.y += tempVelY * speed * deltaTime;
        return proposed;
    }

    void DynamicEntity::snapToGrid(float tileWidth, float tileHeight) {
        // Tile size in world units
        // tileWidth = 2.0f / gridWidth, tileHeight = 2.0f / gridHeight

        // Snap X coordinate to nearest tile boundary
        // We want: pos.x = multiple of tileWidth - 1.0f
        float xInGrid = (pos.x + 1.0f) / tileWidth; // Convert to grid units
        int tileX = static_cast<int>(round(xInGrid));      // Round to nearest tile
        pos.x = tileX * tileWidth - 1.0f;           // Convert back to world

        // Snap Y coordinate to nearest tile boundary
        float yInGrid = (pos.y + 1.0f) / tileHeight;
        int tileY = static_cast<int>(round(yInGrid));
        pos.y = tileY * tileHeight - 1.0f;

        notify(); // Notify observers about position change
    }

} // namespace logic