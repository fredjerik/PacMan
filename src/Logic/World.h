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
        const std::map<Position, bool>& getWalls() const {return m_walls;};
        const int get_gridWidth() const {return gridWidth;}
        const int get_gridHeight() const {return gridHeight;}
        const Size getLogicalTileSize() const {return m_logicalTileSize;}

    private:
        bool isMoveValid(const Position& futurePos, Direction dir) const;
        bool isWallAt(const Position& point) const;

        factory::AbstractFactory* m_factory;
        std::shared_ptr<PacmanEntity> m_pacman;
        // TODO: Add containers for other entities

        std::map<Position, bool> m_walls;
        Size m_logicalTileSize;
        int gridWidth;
        int gridHeight;
    };

} // namespace logic

#endif //PACMAN_WORLD_H
