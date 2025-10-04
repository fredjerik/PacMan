#include "Map.h"
#include <fstream>
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
    }

    void Map::parseTiles() {
        m_wallData.clear();
        m_entityData.clear();
        Size logicalTileSize = getLogicalTileSize();

        for (int y = 0; y < m_gridHeight; ++y) {
            for (int x = 0; x < m_gridWidth; ++x) {
                char tile = m_tiles[y][x];
                Position logicalPos = gridToLogical(x, y);

                switch (tile) {
                    case '#':
                        // For a wall, create a bounding box and add it to the wall data
                        m_wallData.push_back({logicalPos.x - logicalTileSize.width / 2.0f,
                                             logicalPos.y - logicalTileSize.height / 2.0f,
                                             logicalTileSize.width,
                                             logicalTileSize.height});
                        break;
                    case 'p':
                        m_entityData.push_back({EntityType::PACMAN, logicalPos});
                        break;
                    case '.':
                        m_entityData.push_back({EntityType::COIN, logicalPos});
                        break;
                    case 'o':
                        m_entityData.push_back({EntityType::FRUIT, logicalPos});
                        break;
                    case 'g':
                        m_entityData.push_back({EntityType::GHOST, logicalPos});
                        break;
                }
            }
        }
    }

    Position Map::gridToLogical(int x, int y) const {
        float logicalX = ((static_cast<float>(x) + 0.5f) / static_cast<float>(m_gridWidth)) * 2.0f - 1.0f;
        float logicalY = ((static_cast<float>(y) + 0.5f) / static_cast<float>(m_gridHeight)) * 2.0f - 1.0f;
        return {logicalX, logicalY};
    }

    Size Map::getLogicalTileSize() const {
        if (m_gridWidth > 0 && m_gridHeight > 0) {
            return {2.0f / m_gridWidth, 2.0f / m_gridHeight};
        }
        return {0.0f, 0.0f};
    }

    const std::vector<BoundingBox>& Map::getWallData() const {
        return m_wallData;
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
