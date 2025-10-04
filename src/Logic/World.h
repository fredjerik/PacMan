#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H

#include <vector>
#include <memory>
#include <string>
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

    private:
        bool isMoveValid(const BoundingBox& futureBox) const;
        BoundingBox calculateFutureBox(const DynamicEntity& entity, float deltaTime, Direction dir) const;    //TODO:: change so it works with 2 corners.

        factory::AbstractFactory* m_factory;
        std::shared_ptr<PacmanEntity> m_pacman;
        // TODO: Add containers for other entities

        std::vector<BoundingBox> m_walls;
        Size m_logicalTileSize;
    };

} // namespace logic

#endif //PACMAN_WORLD_H
