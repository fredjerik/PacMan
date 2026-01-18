#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H

#include <limits>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "Entities/Dynamic_Entities/DynamicEntity.h"
#include "Entities/Entity.h"
#include "Patterns/AbstractFactory.h"
#include "../Representation/View/Score.h"
#include "Entities/CollectableEntity.h"
#include "Entities/Dynamic_Entities/GhostEntity.h"

namespace logic {

    struct duration
    {
        std::vector<float> CHASE = {20.0f, 20.0f, 20.0f, std::numeric_limits<float>::max()};
        std::vector<float> SCATTER = {7.0f, 7.0f, 5.0f, 5.0f};
        float fear = 6.0f;
        float fear_low = 1.5f;
        float death_delay = 1.3f;
        int phase_index = 0;
        float ghost_init = 5.0f;
    };

    class World
    {
    public:
        explicit World(const std::string& map_path, factory::AbstractFactory* factory);
        ~World() = default;

        void update(float deltaTime);
        void setPacManDirection(Direction dir);
        [[nodiscard]] std::vector<std::weak_ptr<Observer>> getObservers() const;
        [[nodiscard]] const std::vector<std::vector<bool>>& getWallGrid() const { return wall_grid_; }
        [[nodiscard]] const std::map<Position, bool>& getWalls() const { return walls_; }
        [[nodiscard]] int get_gridWidth() const { return grid_width_; }
        [[nodiscard]] int get_gridHeight() const { return grid_height_; }
        [[nodiscard]] Size getLogicalTileSize() const { return tile_size_; }
        [[nodiscard]] bool change_direction(const Position& currentPos, Direction currentDir, Direction newDir) const;
        void set_fear_timer(float fear) { global_duration_.fear = fear; }
        [[nodiscard]] bool victory() const {return victory_;}
        [[nodiscard]] bool defeat() const {return defeat_;}

    private:

        bool isPacmanDying = false;
        float deathAnimationTime = 0;
        int ghosts_eaten;
        duration global_duration_;
        float timer_;
        float fear_timer_;
        float death_timer_ = 0.0f;
        ghost_mode global_ghost_mode_;
        ghost_mode prev_ghost_mode_;

        void start_scatter_mode();
        void start_chase_mode();
        void start_flashing_mode();
        void return_from_fear_mode();
        [[nodiscard]] std::vector<Direction> getPossibleDirections(Position pos, Direction current_direction, ghost_mode ghost_mode) const;
        [[nodiscard]] bool isWallAt(const Position& point) const;
        [[nodiscard]] bool isEntranceAt(const Position& point) const;
        [[nodiscard]] std::pair<int, int> worldToGrid(const Position& pos) const;
        void CollectableCollision();
        [[nodiscard]] bool isValidGridPosition(int gridX, int gridY) const;
        void reset();
        void handle_timer_expired();
        void handle_ghost_releasing(float deltaTime);

        // New method to update ghost chase targets
        void update_ghost_chase_targets();

        // collision
        [[nodiscard]] bool isWallCollision(const Position& entityPos, const Size& entitySize, Direction dir) const;
        [[nodiscard]] bool isGateCollision(const Position& entityPos, const Size& entitySize, Direction dir, ghost_mode mode) const;
        [[nodiscard]] bool checkEntityCollision(const Position& entityPos1, const Size& size1,
                                  const Position& entityPos2, const Size& size2) const;

        factory::AbstractFactory* factory_;
        bool pacman_eaten = false;
        bool victory_ = false;
        bool defeat_ = false;

        //entities
        std::shared_ptr<PacmanEntity> pacman_;
        std::vector<std::shared_ptr<GhostEntity>> ghosts_;
        std::vector<Position> ghost_house;
        std::vector<Position> ghost_gate;
        int coins_left_;
        std::vector<std::vector<std::shared_ptr<CollectableEntity>>> collectable_grid;
        std::map<Position, bool> walls_;
        std::vector<std::vector<bool>> wall_grid_;

        Size tile_size_;
        int grid_width_;
        int grid_height_;
    };

} // namespace logic

#endif //PACMAN_WORLD_H