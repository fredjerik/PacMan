#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H

#include <vector>
#include <string>
#include <map>
#include "Entities/Entity.h" // For logic::Position

namespace logic {

    enum class TileType {
        WALL,
        EMPTY,
        PACMAN,
        GHOST,
        COIN,
        FRUIT
    };

    // Enum to represent the different types of entities
    enum class EntityType {
        PACMAN,
        GHOST,
        COIN,
        FRUIT
    };

    // Struct to hold data for dynamic entity creation
    struct EntityCreationData {
        EntityType type;
        Position position;
    };



    class Map {
    public:
        explicit Map(const std::string& filePath);

        // Getters for the processed data
        const std::map<Position, TileType>& getTileData() const;
        const std::vector<EntityCreationData>& getEntityData() const;
        int getGridWidth() const;
        int getGridHeight() const;

    private:
        void loadFromFile(const std::string& filePath);
        void parseTiles();
        Position gridToTopLeft(int x, int y) const;
        Size getLogicalTileSize() const;

        int m_gridWidth = 0;
        int m_gridHeight = 0;
        std::vector<std::string> m_tiles;
        std::map<Position, TileType> m_tileData;
        std::vector<EntityCreationData> m_entityData;
    };

} // namespace logic

#endif //PACMAN_MAP_H
