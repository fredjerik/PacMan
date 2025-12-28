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
#include "../Representation/View/Score.h"
#include "Entities/CollectableEntity.h"

namespace logic {

    class World {
    public:
        explicit World(const std::string& map_path, factory::AbstractFactory* factory);
        ~World() = default;

        void update(float deltaTime);
        void setPacManDirection(Direction dir);
        std::vector<std::weak_ptr<Observer>> getObservers();
        const std::vector<std::vector<bool>>& getWallGrid() const { return m_wallGrid; }
        const std::map<Position, bool>& getWalls() const { return m_walls; }
        const int get_gridWidth() const { return gridWidth; }
        const int get_gridHeight() const { return gridHeight; }
        const Size getLogicalTileSize() const { return m_logicalTileSize; }
        bool change_direction(const Position& currentPos, Direction currentDir, Direction newDir) const;
        static bool isReverseDirection(Direction dir1, Direction dir2);
        void attach_score(std::shared_ptr<Score> score);
        int get_pacmanlives(){return m_pacman->getLives();};

    private:
        bool isMoveValid(const Position& futurePos, Direction dir) const;
        bool isWallAt(const Position& point) const;
        std::pair<int, int> worldToGrid(const Position& pos) const;
        void CollectableCollision();
        bool isValidGridPosition(int gridX, int gridY) const;

        factory::AbstractFactory* m_factory;
        std::shared_ptr<PacmanEntity> m_pacman;
        std::vector<std::vector<std::shared_ptr<CollectableEntity>>> m_collectableGrid;
        // TODO: Add containers for other entities

        std::map<Position, bool> m_walls;
        std::vector<std::vector<bool>> m_wallGrid;
        Size m_logicalTileSize;
        int gridWidth;
        int gridHeight;
    };

} // namespace logic

#endif //PACMAN_WORLD_H