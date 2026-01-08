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
        std::vector<float> CHASE = {20.0f, 20.0f, 20.0f, std::numeric_limits<float>::max()}; // official timings
        std::vector<float> SCATTER = {7.0f, 7.0f, 5.0f, 5.0f}; // official timings
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
        std::vector<std::weak_ptr<Observer>> getObservers();
        const std::vector<std::vector<bool>>& getWallGrid() const { return wall_grid_; }
        const std::map<Position, bool>& getWalls() const { return walls_; }
        const int get_gridWidth() const { return grid_width_; }
        const int get_gridHeight() const { return grid_height_; }
        const Size getLogicalTileSize() const { return tile_size_; }
        bool change_direction(const Position& currentPos, Direction currentDir, Direction newDir) const;
        static bool isReverseDirection(Direction dir1, Direction dir2);
        static Direction getReverseDirection(Direction dir1);
        void set_fear_timer(float fear) { global_duration_.fear = fear; }
        bool victory() const { if (victory_){ std::cout << "yippie" << std::endl;}return victory_;}
        bool defeat() const {return defeat_;};

    private:
        bool isPacmanDying = false;
        float deathAnimationTime = 0;
        int ghosts_eaten;
        duration global_duration_;
        float timer_;
        float paused_timer;
        ghost_mode global_ghost_mode_;
        ghost_mode prev_ghost_mode_;

        void switch_ghost_mode(bool powerup_eaten);
        std::vector<Direction> getPossibleDirections(Position pos, Direction current_direction, ghost_mode ghost_mode) const;
        void update_ghost_target();
        bool isMoveValid(const Position& futurePos, Direction dir, ghost_mode ghost_mode) const;
        bool isWallAt(const Position& point) const;
        bool isEntranceAt(const Position& point) const;
        std::pair<int, int> worldToGrid(const Position& pos) const;
        void CollectableCollision();
        bool isValidGridPosition(int gridX, int gridY) const;
        void reset();

        // collision
        bool isWallCollision(const Position& entityPos, const Size& entitySize, Direction dir) const;
        bool isGateCollision(const Position& entityPos, const Size& entitySize, Direction dir, ghost_mode mode) const;
        bool checkEntityCollision(const Position& entityPos1, const Size& size1,
                                  const Position& entityPos2, const Size& size2) const;
        // void handlePacmanGhostCollision(std::shared_ptr<GhostEntity> ghost, float delta_time);

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