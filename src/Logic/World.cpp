#include "World.h"
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
        if (gridWidth > 0 && gridHeight > 0) {
            m_logicalTileSize = {2.0f / gridWidth, 2.0f / gridHeight};
        }

        const auto& tileData = map.getTileData();
        for (const auto& pair : tileData) {
            if (pair.second == TileType::WALL) {
                m_walls[pair.first] = true;
            }
        }

        auto entityData = map.getEntityData();
        for (const auto& data : entityData) {
            if (data.type == EntityType::PACMAN) {
                m_pacman = m_factory->create_pacman(data.position, m_logicalTileSize,m_logicalTileSize.width, m_logicalTileSize.height);
            }
            // TODO: Add cases for GHOST, COIN, etc.
        }

        if (!m_pacman) {
            throw std::runtime_error("Map file must contain a Pac-Man starting position ('p').");
        }
    }

    void World::update(float deltaTime) {
        if (m_pacman) {
            Position futurePos = m_pacman->getProposedPosition(deltaTime, m_pacman->getDirection());
            if (isMoveValid(futurePos, m_pacman->getDirection())) {
                m_pacman->update(deltaTime);
            }
            // If move is not valid, do nothing. This prevents the entity from moving and thus shaking.
        }
    }

    void World::setPacManDirection(Direction dir) {
        if (m_pacman) {
            // To check if a direction is valid, we propose a tiny move in that direction
            // and see if it collides with a wall. We use a very small deltaTime
            // to ensure the proposed move is minimal.
            Position futurePos = m_pacman->getProposedPosition(0.001f, dir);
            if (isMoveValid(futurePos, dir)) {
                m_pacman->setDirection(dir);
            }
        }
    }

    bool World::isWallAt(const Position& point) const {
        // This function checks if a single point is inside any wall.
        float tileX = floor((point.x + 1.0f) / m_logicalTileSize.width);
        float tileY = floor((point.y + 1.0f) / m_logicalTileSize.height);
        Position wallPos = {tileX * m_logicalTileSize.width - 1.0f, tileY * m_logicalTileSize.height - 1.0f};
        return m_walls.count(wallPos);
    }

    bool World::isMoveValid(const Position& futurePos, Direction dir) const {
        // futurePos is the top-left corner of the entity's proposed position.
        Position point1, point2;
        
        float inset = m_logicalTileSize.width * 0.1f; // Inset for perpendicular axis
        float epsilon = 1e-5; // Small value to handle boundary conditions

        switch (dir) {
            case Direction::Up:
                point1 = {futurePos.x + inset, futurePos.y};
                point2 = {futurePos.x + m_logicalTileSize.width - inset, futurePos.y};
                break;
            case Direction::Down:
                point1 = {futurePos.x + - inset, futurePos.y + m_logicalTileSize.height - epsilon};
                point2 = {futurePos.x + m_logicalTileSize.width - inset, futurePos.y + m_logicalTileSize.height - epsilon};
                break;
            case Direction::Left:
                point1 = {futurePos.x, futurePos.y + inset};
                point2 = {futurePos.x, futurePos.y + m_logicalTileSize.height - inset};
                break;
            case Direction::Right:
                point1 = {futurePos.x + m_logicalTileSize.width - epsilon, futurePos.y + inset};
                point2 = {futurePos.x + m_logicalTileSize.width - epsilon, futurePos.y + m_logicalTileSize.height - inset};
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
