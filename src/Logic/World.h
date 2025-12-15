#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include "Entities/Dynamic_Entities/DynamicEntity.h"
#include "Entities/Entity.h"
#include "Patterns/AbstractFactory.h"
#include "Map.h" // For BoundingBox

namespace logic {

    class World {
    public:
        explicit World(const std::string& map_path, factory::AbstractFactory* factory);
        ~World() = default;

        void update(float deltaTime);
        void setPacManDirection(Direction dir);
        std::vector<Observer*> getObservers();
        const std::vector<std::vector<bool>>& getWallGrid() const { return m_wallGrid; }
        const std::map<Position, bool>& getWalls() const { return m_walls; }
        const int get_gridWidth() const { return gridWidth; }
        const int get_gridHeight() const { return gridHeight; }
        const Size getLogicalTileSize() const { return m_logicalTileSize; }
        bool change_direction(const Position& currentPos, Direction currentDir, Direction newDir) const;
        static bool isReverseDirection(Direction dir1, Direction dir2);

    private:
        bool isMoveValid(const Position& futurePos, Direction dir) const;
        bool isWallAt(const Position& point) const;

        factory::AbstractFactory* m_factory;
        std::shared_ptr<PacmanEntity> m_pacman;
        // TODO: Add containers for other entities

        std::map<Position, bool> m_walls;
        std::vector<std::vector<bool>> m_wallGrid;
        Size m_logicalTileSize;
        int gridWidth;
        int gridHeight;
    };

} // namespace logic

#endif //PACMAN_WORLD_H