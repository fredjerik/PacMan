#include "World.h"

#include <algorithm>

#include "Map.h"
#include "Patterns/AbstractFactory.h"
#include "Entities/Dynamic_Entities/PacmanEntity.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

namespace logic {

    World::World(const std::string& map_path, factory::AbstractFactory* factory) : m_factory(factory) {
        Map map(map_path);

        gridWidth = map.getGridWidth();
        gridHeight = map.getGridHeight();

        m_wallGrid.resize(gridHeight, std::vector<bool>(gridWidth, false));

        if (gridWidth > 0 && gridHeight > 0) {
            m_logicalTileSize = {2.0f / gridWidth, 2.0f / gridHeight};
        }

        const auto& tileMap = map.getTileData();
        for (const auto& tile : tileMap) {
            if (tile.second == TileType::WALL) {
                m_walls[tile.first] = true;


                float normalizedX = (tile.first.x + 1.0f) / 2.0f;
                float normalizedY = (tile.first.y + 1.0f) / 2.0f;

                int tileX = static_cast<int>(normalizedX * gridWidth + 0.5f); // Round to nearest
                int tileY = static_cast<int>(normalizedY * gridHeight + 0.5f);

                // Ensure we're within bounds
                if (tileX >= 0 && tileX < gridWidth && tileY >= 0 && tileY < gridHeight) {
                    m_wallGrid[tileY][tileX] = true;
                }

                // Debug output
                // std::cout << "Wall at: world(" << tile.first.x << ", " << tile.first.y
                //           << ") -> grid(" << tileX << ", " << tileY << ")" << std::endl;
            }
        }

        auto entityData = map.getEntityData();
        for (const auto& data : entityData) {
            if (data.type == EntityType::PACMAN) {
                m_pacman = m_factory->create_pacman(data.position, m_logicalTileSize.width, m_logicalTileSize.height);
            }
            // TODO: Add cases for GHOST, COIN, etc.
        }

        if (!m_pacman) {
            throw std::runtime_error("Map file must contain a Pac-Man starting position ('p').");
        }

        // Debug: Print grid dimensions
        // std::cout << "Grid size: " << gridWidth << "x" << gridHeight << std::endl;
        // std::cout << "Tile size: " << m_logicalTileSize.width << "x" << m_logicalTileSize.height << std::endl;
    }

    void World::update(float deltaTime) {
        if (m_pacman) {
            Direction currentDir = m_pacman->getDirection();
            Direction nextDir = m_pacman->getNextDirection();
            Position currentPos = m_pacman->getPosition();

            if (nextDir != Direction::None) {
                if (change_direction(currentPos, currentDir, nextDir)) {
                    m_pacman->snapToGrid(m_logicalTileSize.width, m_logicalTileSize.height);

                    Position checkPos = m_pacman->getProposedPosition(0.001f, nextDir);
                    if (isMoveValid(checkPos, nextDir)) {
                        m_pacman->setDirection(nextDir);
                        m_pacman->clearNextDirection();
                    }
                } else if (isReverseDirection(currentDir, nextDir)) {
                    Position checkPos = m_pacman->getProposedPosition(0.001f, nextDir);
                    if (isMoveValid(checkPos, nextDir)) {
                        m_pacman->setDirection(nextDir);
                        m_pacman->clearNextDirection();
                    }
                }
            }
            Position futurePos = m_pacman->getProposedPosition(deltaTime, m_pacman->getDirection());
            if (isMoveValid(futurePos, m_pacman->getDirection())) {
                m_pacman->update(deltaTime);
            } else {
                m_pacman->snapToGrid(m_logicalTileSize.width, m_logicalTileSize.height);
            }
        }
    }

    bool World::isReverseDirection(Direction dir1, Direction dir2) {
        return (dir1 == Direction::Left && dir2 == Direction::Right) ||
               (dir1 == Direction::Right && dir2 == Direction::Left) ||
               (dir1 == Direction::Up && dir2 == Direction::Down) ||
               (dir1 == Direction::Down && dir2 == Direction::Up);
    }

    bool World::change_direction(const Position& currentPos, Direction currentDir, Direction newDir) const {
        bool isReverse =
            (currentDir == Direction::Left && newDir == Direction::Right) ||
            (currentDir == Direction::Right && newDir == Direction::Left) ||
            (currentDir == Direction::Up && newDir == Direction::Down) ||
            (currentDir == Direction::Down && newDir == Direction::Up);

        if (isReverse) {
            return false;
        }

        float gridX = (currentPos.x + 1.0f) / m_logicalTileSize.width;
        float gridY = (currentPos.y + 1.0f) / m_logicalTileSize.height;

        float distToGridLine = 0.0f;

        if (newDir == Direction::Left || newDir == Direction::Right) {
            float alignedY = round(gridY);
            distToGridLine = fabs(gridY - alignedY);
        } else if (newDir == Direction::Up || newDir == Direction::Down) {
            float alignedX = round(gridX);
            distToGridLine = fabs(gridX - alignedX);
        }

        const float SNAP_BUFFER = 0.05f; // 5% of tile size
        return distToGridLine < SNAP_BUFFER;
    }

    void World::setPacManDirection(Direction dir) {
        if (m_pacman) {
            m_pacman->setNextDirection(dir);
        }
    }

    bool World::isWallAt(const Position& point) const {
        float normalizedX = (point.x + 1.0f) / 2.0f;
        float normalizedY = (point.y + 1.0f) / 2.0f;

        const float EPSILON = 1e-5f;
        normalizedX = std::clamp(normalizedX + EPSILON, 0.0f, 1.0f);
        normalizedY = std::clamp(normalizedY + EPSILON, 0.0f, 1.0f);

        // Convert to grid indices
        int tileX = static_cast<int>(normalizedX * gridWidth);
        int tileY = static_cast<int>(normalizedY * gridHeight);

        tileX = std::clamp(tileX, 0, gridWidth - 1);
        tileY = std::clamp(tileY, 0, gridHeight - 1);

        static int debugCounter = 0;
        if (debugCounter++ < 20) {
            // std::cout << "isWallAt: point(" << point.x << ", " << point.y
            //           << ") -> grid(" << tileX << ", " << tileY
            //           << ") -> " << (m_wallGrid[tileY][tileX] ? "WALL" : "EMPTY") << std::endl;
        }

        return m_wallGrid[tileY][tileX];
    }


    bool World::isMoveValid(const Position& futurePos, Direction dir) const {
        Position point1, point2;

        float epsilon = 1e-3;

        switch (dir) {
        case Direction::Up:
            point1 = {futurePos.x + epsilon, futurePos.y};
            point2 = {futurePos.x + m_logicalTileSize.width - epsilon, futurePos.y};
            break;
        case Direction::Down:
            point1 = {futurePos.x + epsilon, futurePos.y + m_logicalTileSize.height};
            point2 = {futurePos.x + m_logicalTileSize.width - epsilon, futurePos.y + m_logicalTileSize.height};
            break;
        case Direction::Left:
            point1 = {futurePos.x, futurePos.y +epsilon};
            point2 = {futurePos.x, futurePos.y + m_logicalTileSize.height-epsilon};
            break;
        case Direction::Right:
            point1 = {futurePos.x + m_logicalTileSize.width, futurePos.y + epsilon};
            point2 = {futurePos.x + m_logicalTileSize.width, futurePos.y + m_logicalTileSize.height - epsilon};
            break;
        case Direction::None:
            return true;
        }

        if (isWallAt(point1) || isWallAt(point2)) {
            return false;
        }

        return true;
    }

    std::vector<Observer*> World::getObservers() {
        std::vector<Observer*> observers;

        if (m_pacman && !m_pacman->getObservers().empty()) {
            observers.push_back(m_pacman->getObservers().at(0).get());
        }
        return observers;
    }

} // namespace logic
