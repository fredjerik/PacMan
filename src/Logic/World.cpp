#include "World.h"

#include <algorithm>

#include "Map.h"
#include "Patterns/AbstractFactory.h"
#include "Entities/Dynamic_Entities/PacmanEntity.h"
#include <stdexcept>
#include <cmath>
#include <utility>
#include <bits/std_function.h>

using namespace std;

namespace logic {

    World::World(const std::string& map_path, factory::AbstractFactory* factory) : factory_(factory)
    {
        const Map map(map_path);

        ghosts_eaten = 0;
        global_duration_ = duration{};
        global_ghost_mode_ = ghost_mode::leaving;
        timer_ = global_duration_.ghost_init;
        grid_width_ = map.getGridWidth();
        grid_height_ = map.getGridHeight();
        coins_left_ = 0;
        wall_grid_.resize(grid_height_, std::vector<bool>(grid_width_, false));

        collectable_grid.resize(grid_height_);
        for (int y = 0; y < grid_height_; y++) {
            collectable_grid[y].resize(grid_width_, nullptr);
        }

        if (grid_width_ > 0 && grid_height_ > 0) {
            tile_size_ = {2.0f / grid_width_, 2.0f / grid_height_};
        }

        const auto& tileMap = map.getTileData();
        for (const auto& tile : tileMap) {
            switch (tile.second)
            {
            case TileType::WALL:
                {
                    walls_[tile.first] = true;


                    float normalizedX = (tile.first.x + 1.0f) / 2.0f;
                    float normalizedY = (tile.first.y + 1.0f) / 2.0f;

                    int tileX = static_cast<int>(normalizedX * grid_width_ + 0.5f);
                    int tileY = static_cast<int>(normalizedY * grid_height_ + 0.5f);

                    if (tileX >= 0 && tileX < grid_width_ && tileY >= 0 && tileY < grid_height_) {
                        wall_grid_[tileY][tileX] = true;
                    }
                    break;
                }
            case TileType::GHOSTHOUSE: ghost_house.emplace_back(tile.first); break;
            case TileType::GHOSTGATE: ghost_gate.emplace_back(tile.first); break;

            case TileType::EMPTY: break;
            }
        }

        auto entityData = map.getEntityData();
        for (const auto& data : entityData) {
            switch (data.type)
            {
            case EntityType::PACMAN:
                pacman_ = factory_->create_pacman(data.position,
                                                    tile_size_.width,
                                                    tile_size_.height);
                break;

            case EntityType::COIN: {
                    auto coin = factory_->create_coin(data.position);
                    auto [gridX, gridY] = worldToGrid(data.position);
                    if (isValidGridPosition(gridX, gridY)) {
                        collectable_grid[gridY][gridX] = coin;
                        coins_left_ += 1;
                    }
                    break;
            }
            case EntityType::POWERUP: {
                    auto powerup = factory_->create_powerup(data.position);
                    auto [gridX, gridY] = worldToGrid(data.position);
                    if (isValidGridPosition(gridX, gridY)) {
                        collectable_grid[gridY][gridX] = powerup;
                    }
                    break;
            }
            case EntityType::FRUIT: {
                    auto fruit = factory_->create_fruit(data.position);
                    auto [gridX, gridY] = worldToGrid(data.position);
                    if (isValidGridPosition(gridX, gridY)) {
                        collectable_grid[gridY][gridX] = fruit;
                    }
                    break;
            }
            }
        }


        ghosts_.emplace_back(factory_->create_blinky(ghost_house, ghost_gate, tile_size_.width,
                                                    tile_size_.height));
        ghosts_.emplace_back(factory_->create_pinky(ghost_house, ghost_gate, tile_size_.width,
                                                    tile_size_.height));
        ghosts_.emplace_back(factory_->create_inky(ghost_house, ghost_gate, tile_size_.width,
                                                       tile_size_.height));
        ghosts_.emplace_back(factory_->create_clyde(ghost_house, ghost_gate, tile_size_.width,
                                                           tile_size_.height));


        for (int i = 0; i < 2; i++)
        {
            ghosts_[i]->leave_house();
        }
        if (!pacman_)
        {
            throw std::runtime_error("Map file must contain a Pac-Man starting position ('p').");
        }
        if (ghost_house.empty())
        {
            throw std::runtime_error("Map file must contain a Ghost House ('g').");
        }
    }

    void World::update(float deltaTime)
    {
        if (pacman_eaten)
        {
            if (timer_ >= 0)
            {
                timer_ -= deltaTime;
                return;
            }
            pacman_eaten = false;
            reset();
            return;
        }
        if (coins_left_ == 0){
        victory_ = true;
        return;
    }
    if (pacman_->getLives() == 0) {
        defeat_ = true;
        return;
    }

    if (pacman_) {
        Direction currentDir = pacman_->getDirection();
        Direction nextDir = pacman_->getNextDirection();
        Position currentPos = pacman_->getPosition();
        Size pacmanSize = {tile_size_.width, tile_size_.height};

        // Handle direction change for Pacman
        if (nextDir != Direction::None) {
            if (change_direction(currentPos, currentDir, nextDir)) {
                pacman_->snapToGrid(tile_size_.width, tile_size_.height);

                Position checkPos = pacman_->getProposedPosition(0.001f, nextDir);
                // Check both wall and gate collisions for Pacman
                bool wallCollision = isWallCollision(checkPos, pacmanSize, nextDir);
                bool gateCollision = isGateCollision(checkPos, pacmanSize, nextDir, ghost_mode::chase);

                if (!wallCollision && !gateCollision) {
                    pacman_->setDirection(nextDir);
                    pacman_->clearNextDirection();
                }
            } else if (isReverseDirection(currentDir, nextDir)) {
                Position checkPos = pacman_->getProposedPosition(0.001f, nextDir);
                bool wallCollision = isWallCollision(checkPos, pacmanSize, nextDir);
                bool gateCollision = isGateCollision(checkPos, pacmanSize, nextDir, ghost_mode::chase);

                if (!wallCollision && !gateCollision) {
                    pacman_->setDirection(nextDir);
                    pacman_->clearNextDirection();
                }
            }
        }

        // Update Pacman position
        Position futurePos = pacman_->getProposedPosition(deltaTime, pacman_->getDirection());
        bool wallCollision = isWallCollision(futurePos, pacmanSize, pacman_->getDirection());
        bool gateCollision = isGateCollision(futurePos, pacmanSize, pacman_->getDirection(), ghost_mode::chase);

        if (!wallCollision && !gateCollision) {
            pacman_->update(deltaTime);
        } else {
            pacman_->snapToGrid(tile_size_.width, tile_size_.height);
        }

        // Check Pacman vs Collectables
        CollectableCollision();
    }

    timer_ -= deltaTime;
    if (global_ghost_mode_ == ghost_mode::leaving)
    {
        // cout << true << endl;
       if (timer_ <= 0)
        {
            timer_ = duration{}.ghost_init;
            for (const auto& ghost : ghosts_)
            {
                if (ghost->get_ghost_mode() == ghost_mode::spawn)
                {
                    ghost->leave_house();
                    break;
                }
            }
        }
    }
    switch_ghost_mode(false);

    Position Blinky_pos;
    for (const auto& ghost : ghosts_) {
        if (ghost->get_ghost_type() == ghost_type::Blinky) {
            Blinky_pos = ghost->getPosition();
        }

        if (checkEntityCollision(pacman_->getProposedPosition(deltaTime, pacman_->getDirection()), pacman_->getSize(),
                        ghost->getPosition(), {ghost->getSize().width, ghost->getSize().height})) {
            ghost_mode mode = ghost->get_ghost_mode();
            if (ghost->get_ghost_mode() == ghost_mode::fear) {
                ghosts_eaten++;
                // Pacman eats ghost
                ghost->eaten();
                // Add score
                ghost->set_score_power(ghosts_eaten);
            } else if (mode != ghost_mode::eaten) {
                // Ghost eats Pacman
                pacman_->loseLife();
                if (pacman_->getLives() >= 0) {
                    pacman_eaten = true;
                    timer_ = global_duration_.death_delay;
                    return;
                }
            }
        }

        ghost_mode currentGhostMode = ghost->get_ghost_mode();
        const Direction prevDir = ghost->getDirection();
        Size ghostSize = {tile_size_.width, tile_size_.height};

        // Get possible directions for ghost (need to update this function too)
        std::vector<Direction> possible_dirs = getPossibleDirections(
            ghost->getProposedPosition(0.001f, prevDir),
            prevDir, currentGhostMode);

        // for (auto dir : possible_dirs)
        // {
        //     cout << DynamicEntity::to_string(dir) << ", ";
        // }
        // cout << endl;

        if (ghost->changed_directions(possible_dirs)) {
            ghost->calculate_direction(possible_dirs);
            const Direction new_dir = ghost->getDirection();

            if (prevDir != Direction::None && prevDir != new_dir) {
                ghost->snapToGrid(tile_size_.width, tile_size_.height);
            }
        }

        Position futurePos = ghost->getProposedPosition(deltaTime, ghost->getDirection());
        bool wallCollision = isWallCollision(futurePos, ghostSize, ghost->getDirection());
        bool gateCollision = isGateCollision(futurePos, ghostSize, ghost->getDirection(), currentGhostMode);

        if (!wallCollision && !gateCollision) {
            ghost->update(deltaTime);
        } else {
            // Collision - snap to grid
            ghost->snapToGrid(tile_size_.width, tile_size_.height);

            // If stuck, allow reverse
            if (possible_dirs.empty()) {
                Direction reverseDir = getReverseDirection(ghost->getDirection());
                Position checkPos = ghost->getProposedPosition(0.001f, reverseDir);
                bool reverseWallCollision = isWallCollision(checkPos, ghostSize, reverseDir);
                bool reverseGateCollision = isGateCollision(checkPos, ghostSize, reverseDir, currentGhostMode);

                if (!reverseWallCollision && !reverseGateCollision) {
                    ghost->setDirection(reverseDir);
                }
            }
        }
    }

    // Ghost chasing logic
    if (global_ghost_mode_ == ghost_mode::chase) {
        for (const auto& ghost : ghosts_) {
            ChaseData chase_data;
            chase_data.pacman_pos = pacman_->getPosition();
            switch (ghost->get_ghost_type()) {
                case ghost_type::Blinky:
                    ghost->chase(chase_data);
                    break;
                case ghost_type::Pinky:
                    chase_data.pacman_dir = pacman_->getDirection();
                    ghost->chase(chase_data);
                    break;
                case ghost_type::Inky:
                    chase_data.pacman_dir = pacman_->getDirection();
                    chase_data.blinky_pos = Blinky_pos;
                    ghost->chase(chase_data);
                    break;
                case ghost_type::Clyde:
                    ghost->chase(chase_data);
                    break;
            }
        }
    }
}

    void World::reset()
    {
        global_duration_ = duration{};
        global_ghost_mode_ = ghost_mode::leaving;
        timer_ = std::numeric_limits<float>::max();
        paused_timer = 0;
        ghosts_eaten = 0;      // Reset ghost eaten counter if needed

        pacman_->reset();

        // Give Pacman an initial direction after reset
        pacman_->setDirection(Direction::Right);  // Or whichever default direction you want
        pacman_->clearNextDirection();

        for (const auto& ghost : ghosts_)
        {
            ghost->reset();
            // You might also need to give ghosts an initial direction
            // ghost->setDirection(Direction::Left); // Example
        }
    }

    Direction World::getReverseDirection(Direction currentDir)
    {
        switch (currentDir)
        {
            case Direction::Left: return Direction::Right;
            case Direction::Right: return Direction::Left;
            case Direction::Up: return Direction::Up;
            case Direction::Down: return Direction::Down;
            default: return Direction::None;
        }
    }

    bool World::isReverseDirection(Direction dir1, Direction dir2) {
        return (dir1 == Direction::Left && dir2 == Direction::Right) ||
               (dir1 == Direction::Right && dir2 == Direction::Left) ||
               (dir1 == Direction::Up && dir2 == Direction::Down) ||
               (dir1 == Direction::Down && dir2 == Direction::Up);
    }

    bool World::change_direction(const Position& currentPos, Direction currentDir, Direction newDir) const {
        if (isReverseDirection(currentDir, newDir)) {
            return false;
        }

        float gridX = (currentPos.x + 1.0f) / tile_size_.width;
        float gridY = (currentPos.y + 1.0f) / tile_size_.height;

        float distToGridLine = 0.0f;

        if (newDir == Direction::Left || newDir == Direction::Right) {
            float alignedY = round(gridY);
            distToGridLine = fabs(gridY - alignedY);
        } else if (newDir == Direction::Up || newDir == Direction::Down) {
            float alignedX = round(gridX);
            distToGridLine = fabs(gridX - alignedX);
        }

        const float SNAP_BUFFER = 0.05f;
        return distToGridLine < SNAP_BUFFER;
    }

    void World::setPacManDirection(Direction dir)
    {
        if (pacman_) {
            Direction currentDir = pacman_->getDirection();

            if (dir != currentDir) {
                pacman_->setNextDirection(dir);
            }
        }
    }

    void World::switch_ghost_mode(bool powerup_eaten)
    {
        if (powerup_eaten)
        {
            prev_ghost_mode_ = global_ghost_mode_;
            paused_timer = timer_;
            for (const auto& ghost : ghosts_)
            {
                ghost->fear(pacman_->getPosition());
            }
            global_ghost_mode_ = ghost_mode::fear;
            timer_ = global_duration_.fear;
            return;
        }
        if (global_ghost_mode_ == ghost_mode::leaving)
        {
            for (const auto& ghost : ghosts_)
            {
                if (ghost->get_ghost_mode() != ghost_mode::scatter)
                {
                    return;
                }
            }
            global_ghost_mode_ = ghost_mode::scatter;
            // cout << "switching ghost mode to: " << GhostEntity::to_string(global_ghost_mode_) << endl;
            timer_ = global_duration_.SCATTER[global_duration_.phase_index];
        }


        if (global_ghost_mode_ == ghost_mode::chase && timer_ <= 0)
        {
            global_ghost_mode_ = ghost_mode::scatter;
            // cout << "switching ghost mode to: " << GhostEntity::to_string(global_ghost_mode_) << endl;
            global_duration_.phase_index += 1;
            if (global_duration_.phase_index >= global_duration_.SCATTER.size())
            {
                cout << "CHASE vector out of bounds (You should be physically dead by now)" << endl;
                exit(0);
            }
            timer_ = global_duration_.SCATTER[global_duration_.phase_index];
            for (const auto& ghost: ghosts_)
            {
                ghost->scatter();
            }
            return;
        }

        if (global_ghost_mode_ == ghost_mode::scatter && timer_ <= 0)
        {
            global_ghost_mode_ = ghost_mode::chase;
            // cout << "switching ghost mode to: " << GhostEntity::to_string(global_ghost_mode_) << endl;
            global_duration_.phase_index += 1;
            if (global_duration_.phase_index >= global_duration_.CHASE.size())
            {
                cerr << "SCATTER vector out of bounds (this should never happen)" << endl;
                exit(-1);
            }
            timer_ = global_duration_.CHASE[global_duration_.phase_index];
            return;
        }

        if (global_ghost_mode_ == ghost_mode::fear && timer_ <= 0)
        {
            for (const auto& ghost: ghosts_)
            {
                ghost->leave_house();
            }
            global_ghost_mode_ = prev_ghost_mode_;
            timer_ = paused_timer;
            return;
        }
        if (global_ghost_mode_ == ghost_mode::fear && timer_ <= global_duration_.fear_low)
        {
            for (const auto& ghost: ghosts_)
            {
                ghost->low_fear();
            }
        }
    }

    bool World::isValidGridPosition(int gridX, int gridY) const {
        return gridX >= 0 && gridX < grid_width_ &&
               gridY >= 0 && gridY < grid_height_;
    }

    void World::CollectableCollision() {
    if (!pacman_) return;

    Position pacmanPos = pacman_->getPosition();
    Direction dir = pacman_->getDirection();

    if (dir == Direction::None) return;

    float epsilon = 1e-3f;
    Position checkPoint;

    switch (dir) {
    case Direction::Up:
        checkPoint = {pacmanPos.x + tile_size_.width / 2.0f,
                      pacmanPos.y + epsilon};
        break;
    case Direction::Down:
        checkPoint = {pacmanPos.x + tile_size_.width / 2.0f,
                      pacmanPos.y + tile_size_.height - epsilon};
        break;
    case Direction::Left:
        checkPoint = {pacmanPos.x + epsilon,
                      pacmanPos.y + tile_size_.height / 2.0f};
        break;
    case Direction::Right:
        checkPoint = {pacmanPos.x + tile_size_.width - epsilon,
                      pacmanPos.y + tile_size_.height / 2.0f};
        break;
    case Direction::None: break;
    }

    auto [gridX, gridY] = worldToGrid(checkPoint);

    if (!isValidGridPosition(gridX, gridY)) return;

    auto& collectable = collectable_grid[gridY][gridX];
    if (!collectable) {
        return;
    }


    Size collectableSize = collectable->getSize();

    float collectableWidth = tile_size_.width * collectableSize.width;
    float collectableHeight = tile_size_.height * collectableSize.height;

    float cellCenterX = (gridX + 0.5f) * tile_size_.width - 1.0f;
    float cellCenterY = (gridY + 0.5f) * tile_size_.height - 1.0f;

    float collectableLeft = cellCenterX - collectableWidth / 2.0f;
    float collectableRight = cellCenterX + collectableWidth / 2.0f;
    float collectableTop = cellCenterY - collectableHeight / 2.0f;
    float collectableBottom = cellCenterY + collectableHeight / 2.0f;

    bool pointInCollectable =
        (checkPoint.x >= collectableLeft) &&
        (checkPoint.x <= collectableRight) &&
        (checkPoint.y >= collectableTop) &&
        (checkPoint.y <= collectableBottom);

    if (pointInCollectable) {
        if (collectable->getType() == CollectableType::PowerUp) switch_ghost_mode(true);
        if (collectable->getType() == CollectableType::Coin) coins_left_--;
        collectable->onCollected();
        collectable = nullptr;
    }
}

    bool World::isWallAt(const Position& point) const {
         auto [tileX, tileY] = worldToGrid(point);
         return wall_grid_[tileY][tileX];
     }

    bool World::isEntranceAt(const Position& point) const {
         auto [tileX, tileY] = worldToGrid(point);

         for (const auto& gatePos : ghost_gate) {
             auto [gateX, gateY] = worldToGrid(gatePos);
             if (gateX == tileX && gateY == tileY) {
                 return true;
             }
         }

         return false;
     }

    std::vector<std::weak_ptr<Observer>> World::getObservers()
    {
        std::vector<std::weak_ptr<Observer>> viewObservers;

        for (int y = 0; y < get_gridHeight(); y++) {
            for (int x = 0; x < get_gridWidth(); x++) {
                if (auto collectable = collectable_grid[y][x]) {
                    const auto& observers = collectable->getObservers();
                    if (!observers.empty()) {
                        viewObservers.push_back(observers[0]);
                    }
                }
            }
        }
        if (pacman_) {
            const auto& pacmanObservers = pacman_->getObservers();
            for (const auto& observer : pacmanObservers) {
                // observer is shared_ptr, convert to weak_ptr
                viewObservers.push_back(observer);
            }
        }

        for (const auto& ghost : ghosts_)
        {
            const auto& ghostObservers = ghost->getObservers();
            viewObservers.push_back(ghostObservers[0]);
        }

        return viewObservers;
    }

    bool World::isWallCollision(const Position& entityPos, const Size& entitySize, Direction dir) const {
        // Calculate which grid cells the entity's leading edge touches
        Position point1, point2;
        float epsilon = 1e-3;

        switch (dir) {
        case Direction::Up:
            point1 = {entityPos.x + epsilon, entityPos.y};
            point2 = {entityPos.x + entitySize.width - epsilon, entityPos.y};
            break;
        case Direction::Down:
            point1 = {entityPos.x + epsilon, entityPos.y + entitySize.height};
            point2 = {entityPos.x + entitySize.width - epsilon, entityPos.y + entitySize.height};
            break;
        case Direction::Left:
            point1 = {entityPos.x, entityPos.y + epsilon};
            point2 = {entityPos.x, entityPos.y + entitySize.height - epsilon};
            break;
        case Direction::Right:
            point1 = {entityPos.x + entitySize.width, entityPos.y + epsilon};
            point2 = {entityPos.x + entitySize.width, entityPos.y + entitySize.height - epsilon};
            break;
        case Direction::None:
            return false; // No movement, no wall collision
        }

        // Check both edge points against wall grid
        return isWallAt(point1) || isWallAt(point2);
    }

    bool World::isGateCollision(const Position& entityPos, const Size& entitySize,
                               Direction dir, ghost_mode mode) const {
        // Same edge calculation as wall collision
        Position point1, point2;
        float epsilon = 1e-3;

        switch (dir) {
        case Direction::Up:
            point1 = {entityPos.x + epsilon, entityPos.y};
            point2 = {entityPos.x + entitySize.width - epsilon, entityPos.y};
            break;
        case Direction::Down:
            point1 = {entityPos.x + epsilon, entityPos.y + entitySize.height};
            point2 = {entityPos.x + entitySize.width - epsilon, entityPos.y + entitySize.height};
            break;
        case Direction::Left:
            point1 = {entityPos.x, entityPos.y + epsilon};
            point2 = {entityPos.x, entityPos.y + entitySize.height - epsilon};
            break;
        case Direction::Right:
            point1 = {entityPos.x + entitySize.width, entityPos.y + epsilon};
            point2 = {entityPos.x + entitySize.width, entityPos.y + entitySize.height - epsilon};
            break;
        case Direction::None:
            return false;
        }

        // Check if edge touches gate
        bool touchesGate = isEntranceAt(point1) || isEntranceAt(point2);

        if (!touchesGate) return false;

        // Gate permission rules (ghosts only in special modes)
        bool canPassGate = (mode == ghost_mode::eaten ||
                           mode == ghost_mode::leaving ||
                           mode == ghost_mode::entering);

        // Return true if CAN'T pass (collision occurs)
        return !canPassGate;
    }

    bool World::checkEntityCollision(const Position& entityPos1, const Size& size1,
                                        const Position& entityPos2, const Size& size2) const {
            // Convert multipliers to actual sizes
            float actualWidth1 = tile_size_.width * size1.width;
            float actualHeight1 = tile_size_.height * size1.height;
            float actualWidth2 = tile_size_.width * size2.width;
            float actualHeight2 = tile_size_.height * size2.height;

            // Now do AABB with actual sizes
            return !(entityPos1.x + actualWidth1 < entityPos2.x ||
                     entityPos1.x > entityPos2.x + actualWidth2 ||
                     entityPos1.y + actualHeight1 < entityPos2.y ||
                     entityPos1.y > entityPos2.y + actualHeight2);
    }

    std::pair<int, int> World::worldToGrid(const Position& point) const {
        float normalizedX = (point.x + 1.0f) / 2.0f;
        float normalizedY = (point.y + 1.0f) / 2.0f;

        const float EPSILON = 1e-5f;
        normalizedX = std::clamp(normalizedX + EPSILON, 0.0f, 1.0f);
        normalizedY = std::clamp(normalizedY + EPSILON, 0.0f, 1.0f);

        int tileX = static_cast<int>(normalizedX * grid_width_);
        int tileY = static_cast<int>(normalizedY * grid_height_);

        tileX = std::clamp(tileX, 0, grid_width_ - 1);
        tileY = std::clamp(tileY, 0, grid_height_ - 1);

        return {tileX, tileY};
    }

    std::vector<Direction> World::getPossibleDirections(Position pos, Direction current_direction,
                                                   ghost_mode mode) const {
    std::vector<Direction> possible;
    float epsilon = 1e-3;
    Size entitySize = {tile_size_.width, tile_size_.height};

    // Check UP
    if (!isReverseDirection(current_direction, Direction::Up)) {
        Position checkPos = pos;
        checkPos.y -= epsilon;
        bool wallCollision = isWallCollision(checkPos, entitySize, Direction::Up);
        bool gateCollision = isGateCollision(checkPos, entitySize, Direction::Up, mode);
        if (!wallCollision && !gateCollision) {
            possible.push_back(Direction::Up);
        }
    }

    // Check LEFT
    if (!isReverseDirection(current_direction, Direction::Left)) {
        Position checkPos = pos;
        checkPos.x -= epsilon;
        bool wallCollision = isWallCollision(checkPos, entitySize, Direction::Left);
        bool gateCollision = isGateCollision(checkPos, entitySize, Direction::Left, mode);
        if (!wallCollision && !gateCollision) {
            possible.push_back(Direction::Left);
        }
    }

    // Check DOWN
    if (!isReverseDirection(current_direction, Direction::Down)) {
        Position checkPos = pos;
        checkPos.y += epsilon;
        bool wallCollision = isWallCollision(checkPos, entitySize, Direction::Down);
        bool gateCollision = isGateCollision(checkPos, entitySize, Direction::Down, mode);
        if (!wallCollision && !gateCollision) {
            possible.push_back(Direction::Down);
        }
    }

    // Check RIGHT
    if (!isReverseDirection(current_direction, Direction::Right)) {
        Position checkPos = pos;
        checkPos.x += epsilon;
        bool wallCollision = isWallCollision(checkPos, entitySize, Direction::Right);
        bool gateCollision = isGateCollision(checkPos, entitySize, Direction::Right, mode);
        if (!wallCollision && !gateCollision) {
            possible.push_back(Direction::Right);
        }
    }

    return possible;
}

}; // namespace logic