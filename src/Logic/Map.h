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
        GHOSTGATE,
        GHOSTHOUSE
    };

    enum class EntityType {
        PACMAN,
        COIN,
        POWERUP,
        FRUIT
    };

    struct EntityCreationData {
        EntityType type;
        Position position;
    };



    class Map {
    public:
        explicit Map(const std::string& filePath);

        [[nodiscard]] const std::map<Position, TileType>& getTileData() const;
        [[nodiscard]] const std::vector<EntityCreationData>& getEntityData() const;
        [[nodiscard]] int getGridWidth() const;
        [[nodiscard]] int getGridHeight() const;

    private:
        void loadFromFile(const std::string& filePath);
        void parseTiles();
        [[nodiscard]] Position gridToTopLeft(int x, int y) const;
        [[nodiscard]] Size getLogicalTileSize() const;

        int m_gridWidth = 0;
        int m_gridHeight = 0;
        std::vector<std::string> m_tiles;
        std::map<Position, TileType> m_tileData;
        std::vector<EntityCreationData> m_entityData;
    };

} // namespace logic

#endif //PACMAN_MAP_H
