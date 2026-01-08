#include "Map.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace logic {

    Map::Map(const std::string& filePath) {
        loadFromFile(filePath);
        parseTiles();
    }

    void Map::loadFromFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open map file: " + filePath);
        }

        std::string line;
        while (std::getline(file, line)) {
            m_tiles.push_back(line);
        }
        file.close();

        if (m_tiles.empty()) {
            throw std::runtime_error("Map file is empty: " + filePath);
        }

        m_gridHeight = m_tiles.size();
        m_gridWidth = m_tiles.empty() ? 0 : m_tiles[0].size();

        for (auto& row : m_tiles) {
            row.resize(m_gridWidth, ' ');
        }
    }

    void Map::parseTiles() {
        m_tileData.clear();
        m_entityData.clear();

        for (int y = 0; y < m_gridHeight; ++y) {
            for (int x = 0; x < m_gridWidth; ++x) {
                char tileChar = m_tiles[y][x];
                Position topLeftPos = gridToTopLeft(x, y);
                TileType tileType = TileType::EMPTY;
                EntityType entityType;
                bool isEntity = false;

                switch (tileChar) {
                    case '#':
                        tileType = TileType::WALL;
                        break;
                    case 'p':
                        entityType = EntityType::PACMAN;
                        isEntity = true;
                        break;
                    case '.':
                        entityType = EntityType::COIN;
                        isEntity = true;
                        break;
                    case 'o':
                        entityType = EntityType::POWERUP;
                        isEntity = true;
                        break;
                    case 'f':
                        entityType = EntityType::FRUIT;
                        isEntity = true;
                        break;
                    case 'g':
                        tileType = TileType::GHOSTHOUSE;
                        break;
                    case '-':
                        tileType = TileType::GHOSTGATE;
                        break;
                    default:
                        tileType = TileType::EMPTY;
                        break;
                }

                m_tileData[topLeftPos] = tileType;

                if (isEntity) {
                    m_entityData.push_back({entityType, topLeftPos});
                }
            }
        }
    }

    Position Map::gridToTopLeft(int x, int y) const {
        float logicalX = (static_cast<float>(x) / static_cast<float>(m_gridWidth)) * 2.0f - 1.0f;
        float logicalY = (static_cast<float>(y) / static_cast<float>(m_gridHeight)) * 2.0f - 1.0f;
        return {logicalX, logicalY};
    }

    Size Map::getLogicalTileSize() const {
        if (m_gridWidth > 0 && m_gridHeight > 0) {
            return {2.0f / m_gridWidth, 2.0f / m_gridHeight};
        }
        return {0.0f, 0.0f};
    }

    const std::map<Position, TileType>& Map::getTileData() const {
        return m_tileData;
    }

    const std::vector<EntityCreationData>& Map::getEntityData() const {
        return m_entityData;
    }

    int Map::getGridWidth() const {
        return m_gridWidth;
    }

    int Map::getGridHeight() const {
        return m_gridHeight;
    }

} // namespace logic