#include "World.h"

#include <algorithm>

#include "Map.h"
#include "Patterns/AbstractFactory.h"
#include "Entities/Dynamic_Entities/PacmanEntity.h"
#include <stdexcept>
#include <cmath>

using namespace std;

namespace logic {

    World::World(const std::string& map_path, factory::AbstractFactory* factory) : m_factory(factory) {
        Map map(map_path);

        gridWidth = map.getGridWidth();
        gridHeight = map.getGridHeight();

        m_wallGrid.resize(gridHeight, std::vector<bool>(gridWidth, false));

        m_collectableGrid.resize(gridHeight);
        for (int y = 0; y < gridHeight; y++) {
            m_collectableGrid[y].resize(gridWidth, nullptr);
        }

        if (gridWidth > 0 && gridHeight > 0) {
            m_logicalTileSize = {2.0f / gridWidth, 2.0f / gridHeight};
        }

        const auto& tileMap = map.getTileData();
        for (const auto& tile : tileMap) {
            if (tile.second == TileType::WALL) {
                m_walls[tile.first] = true;


                float normalizedX = (tile.first.x + 1.0f) / 2.0f;
                float normalizedY = (tile.first.y + 1.0f) / 2.0f;

                int tileX = static_cast<int>(normalizedX * gridWidth + 0.5f);
                int tileY = static_cast<int>(normalizedY * gridHeight + 0.5f);

                if (tileX >= 0 && tileX < gridWidth && tileY >= 0 && tileY < gridHeight) {
                    m_wallGrid[tileY][tileX] = true;
                }

            }
        }

        auto entityData = map.getEntityData();
        for (const auto& data : entityData) {
            switch (const EntityType& type = data.type)
            {
                case EntityType::PACMAN:
                    m_pacman = m_factory->create_pacman(data.position,
                                                        m_logicalTileSize.width,
                                                        m_logicalTileSize.height);
                    break;

                case EntityType::COIN: {
                        auto coin = m_factory->create_coin(data.position);
                        auto [gridX, gridY] = worldToGrid(data.position);
                        if (isValidGridPosition(gridX, gridY)) {
                            m_collectableGrid[gridY][gridX] = coin;
                        }
                        break;
                }
                case EntityType::POWERUP: {
                            auto powerup = m_factory->create_powerup(data.position);
                            auto [gridX, gridY] = worldToGrid(data.position);
                            if (isValidGridPosition(gridX, gridY)) {
                                m_collectableGrid[gridY][gridX] = powerup;
                            }
                            break;
                }
                case EntityType::FRUIT: {
                            auto fruit = m_factory->create_fruit(data.position);
                            auto [gridX, gridY] = worldToGrid(data.position);
                            if (isValidGridPosition(gridX, gridY)) {
                                m_collectableGrid[gridY][gridX] = fruit;
                            }
                            break;
                }
            }
        }

        if (!m_pacman) {
            throw std::runtime_error("Map file must contain a Pac-Man starting position ('p').");
        }
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
            CollectableCollision();
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

        const float SNAP_BUFFER = 0.05f;
        return distToGridLine < SNAP_BUFFER;
    }

    void World::setPacManDirection(Direction dir)
    {
        if (m_pacman) {
            Direction currentDir = m_pacman->getDirection();

            if (dir != currentDir) {
                m_pacman->setNextDirection(dir);
            }
        }
    }

    bool World::isValidGridPosition(int gridX, int gridY) const {
        return gridX >= 0 && gridX < gridWidth &&
               gridY >= 0 && gridY < gridHeight;
    }

void World::CollectableCollision() {
    if (!m_pacman) return;

    Position pacmanPos = m_pacman->getPosition();
    Direction dir = m_pacman->getDirection();

    if (dir == Direction::None) return;

    float epsilon = 1e-3f;
    Position checkPoint;

    switch (dir) {
    case Direction::Up:
        checkPoint = {pacmanPos.x + m_logicalTileSize.width / 2.0f,
                      pacmanPos.y + epsilon};
        break;
    case Direction::Down:
        checkPoint = {pacmanPos.x + m_logicalTileSize.width / 2.0f,
                      pacmanPos.y + m_logicalTileSize.height - epsilon};
        break;
    case Direction::Left:
        checkPoint = {pacmanPos.x + epsilon,
                      pacmanPos.y + m_logicalTileSize.height / 2.0f};
        break;
    case Direction::Right:
        checkPoint = {pacmanPos.x + m_logicalTileSize.width - epsilon,
                      pacmanPos.y + m_logicalTileSize.height / 2.0f};
        break;
    }

    auto [gridX, gridY] = worldToGrid(checkPoint);

    if (!isValidGridPosition(gridX, gridY)) return;

    auto& collectable = m_collectableGrid[gridY][gridX];
    if (!collectable) {
        return;
    }


    Size collectableSize = collectable->getSize();

    float collectableWidth = m_logicalTileSize.width * collectableSize.width;
    float collectableHeight = m_logicalTileSize.height * collectableSize.height;

    float cellCenterX = (gridX + 0.5f) * m_logicalTileSize.width - 1.0f;  // Convert to world [-1,1]
    float cellCenterY = (gridY + 0.5f) * m_logicalTileSize.height - 1.0f;

    float collectableLeft = cellCenterX - collectableWidth / 2.0f;
    float collectableRight = cellCenterX + collectableWidth / 2.0f;
    float collectableTop = cellCenterY - collectableHeight / 2.0f;
    float collectableBottom = cellCenterY + collectableHeight / 2.0f;

    bool pointInCollectable =
        (checkPoint.x >= collectableLeft) &&
        (checkPoint.x <= collectableRight) &&
        (checkPoint.y >= collectableTop) &&
        (checkPoint.y <= collectableBottom);

    if (pointInCollectable) {
        collectable->onCollected();
        collectable = nullptr;
    }
}
    bool World::isWallAt(const Position& point) const {
        auto [tileX, tileY] = worldToGrid(point);
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

    std::vector<std::weak_ptr<Observer>> World::getObservers() {
        std::vector<std::weak_ptr<Observer>> viewObservers;

        for (int y = 0; y < gridHeight; y++) {
            for (int x = 0; x < gridWidth; x++) {
                if (auto collectable = m_collectableGrid[y][x]) {
                    const auto& observers = collectable->getObservers();
                    if (!observers.empty()) {
                        // observers[0] is already a shared_ptr, convert to weak_ptr
                        viewObservers.push_back(observers[0]);
                    }
                }
            }
        }

        if (m_pacman) {
            const auto& pacmanObservers = m_pacman->getObservers();
            for (const auto& observer : pacmanObservers) {
                // observer is shared_ptr, convert to weak_ptr
                viewObservers.push_back(observer);
            }
        }

        return viewObservers;
    }

    std::pair<int, int> World::worldToGrid(const Position& point) const {
        float normalizedX = (point.x + 1.0f) / 2.0f;
        float normalizedY = (point.y + 1.0f) / 2.0f;

        const float EPSILON = 1e-5f;
        normalizedX = std::clamp(normalizedX + EPSILON, 0.0f, 1.0f);
        normalizedY = std::clamp(normalizedY + EPSILON, 0.0f, 1.0f);

        int tileX = static_cast<int>(normalizedX * gridWidth);
        int tileY = static_cast<int>(normalizedY * gridHeight);

        tileX = std::clamp(tileX, 0, gridWidth - 1);
        tileY = std::clamp(tileY, 0, gridHeight - 1);

        return {tileX, tileY};
    }
} // namespace logic
