#include "GhostEntity.h"
#include <iostream>
#include <cmath>

#include "Singleton/Random.h"

namespace logic
{
    GhostEntity::GhostEntity(ghost_type ghost_type, const std::vector<Position>& ghost_house,
                             const std::vector<Position>& ghost_gate,
                             Position scatter_position,
                             float velX_unit, float velY_unit)
        : DynamicEntity(ghost_house[0], Size{1, 1}, velX_unit, velY_unit, 3.8f),
                        ghost_type_(ghost_type), scatter_corner_(scatter_position), ghost_house_(ghost_house), ghost_gate_(ghost_gate)
    {
        // update_target_ = true;
        frame_counter = 0;
        spawn_ = std::make_pair(ghost_gate[0], findClosestHousePosition(ghost_gate[0], ghost_house));
        target = spawn_.second;
        ghost_mode_ = ghost_mode::spawn;
        lastPossibleDirections = {Direction::None};
    }

    Position GhostEntity::random()
    {
        auto& random = singleton::Random::get_instance();
        float x = random.get_float(-1.0f, 1.0f);
        float y = random.get_float(-1.0f, 1.0f);
        return Position{x, y};
    }

    bool GhostEntity::should_update()
    {
        if (ghost_mode_ == ghost_mode::chase || ghost_mode_ == ghost_mode::fear)
        {
            frame_counter++;
            if (frame_counter > 6)
                return true;
        }
        return false;
    }

    void GhostEntity::update(float deltaTime) {

        if (ghost_mode_ == ghost_mode::leaving && distance(pos_, spawn_.first) < EPSILON){
            scatter();
        }

        if (ghost_mode_ == ghost_mode::eaten) {
            for (const auto& gatePos : ghost_gate_) {
                if (distance(pos_, gatePos) < EPSILON) {
                    // std::cout << "entering" << std::endl;
                    target = spawn_.second;
                    ghost_mode_ = ghost_mode::entering;
                    OnEvent(GameEvent::GhostModeChanged, 0);
                    break;
                }
            }
        }

        // Check if entering ghost reached ANY house tile
        else if (ghost_mode_ == ghost_mode::entering) {
            for (const auto& housePos : ghost_house_) {
                if (distance(pos_, housePos) < EPSILON) {
                    target = spawn_.first; // Go back to gate
                    ghost_mode_ = ghost_mode::leaving;
                    break;
                }
            }
        }

        // std::cout << target.x << ", " << target.y << std::endl;
        pos_.x += velX * speed_ * deltaTime;
        pos_.y += velY * speed_ * deltaTime;
        // std::cout << DynamicEntity::to_string(irection) << std::endl;
        notify();
    }

    Position GhostEntity::findClosestHousePosition(const Position& gate_pos,
                                               const std::vector<Position>& ghost_house) {
        if (ghost_house.empty()) return gate_pos;

        Position closest = ghost_house[0];
        float minDist = distance(gate_pos, closest);

        for (size_t i = 1; i < ghost_house.size(); i++) {
            float dist = distance(gate_pos, ghost_house[i]);
            if (dist < minDist) {
                minDist = dist;
                closest = ghost_house[i];
            }
        }
        return closest;
    }

    void GhostEntity::fear(const Position& pacman_position)
    {
        ghost_mode_ = ghost_mode::fear;
        OnEvent(GameEvent::GhostModeChanged, 1);
        if (distance(pos_,pacman_position) > visibility_)
        {
            target = random();
        }
        else
        {
            //actively runs away from pacman if pacman is within the visibility range.
            float dx = pos_.x - pacman_position.x;
            float dy = pos_.y - pacman_position.y;

            target.x = pos_.x + dx;
            target.y = pos_.y + dy;
        }
    }

    void GhostEntity::scatter()
    {
        ghost_mode_ = ghost_mode::scatter;
        OnEvent(GameEvent::GhostModeChanged, 0);        target = scatter_corner_;
    }
    void GhostEntity::eaten()
    {
        // std::cout << "eaten" << std::endl;
        ghost_mode_ = ghost_mode::eaten;
        OnEvent(GameEvent::GhostModeChanged, 3);
        OnEvent(GameEvent::GhostEaten, pow(2,score_power_) * 200);
        target = spawn_.first;
    }

    void GhostEntity::calculate_direction(const std::vector<Direction>& possible_directions) {
        if (possible_directions.empty()) return;

        float shortest_distance = std::numeric_limits<float>::max();
        Direction bestDirection = possible_directions[0];

        for (auto direction : possible_directions) {
            Position nextTilePos = pos_;

            switch (direction) { // we can move one tile because the next possible intersection is at this position.
            case Direction::Up:
                nextTilePos.y -= size_.height; // Move up one tile
                break;
            case Direction::Down:
                nextTilePos.y += size_.height; // Move down one tile
                break;
            case Direction::Left:
                nextTilePos.x -= size_.width;  // Move left one tile
                break;
            case Direction::Right:
                nextTilePos.x += size_.width;  // Move right one tile
                break;
            case Direction::None:
                continue;
            }

            float delta = distance(nextTilePos, target);

            float tolerance = size_.width * 0.01f;

            if (delta < shortest_distance - tolerance) {
                shortest_distance = delta;
                bestDirection = direction;
            }
        }

        setDirection(bestDirection);
        OnEvent(GameEvent::DirectionChanged, static_cast<int>(bestDirection));
    }// up left down right. priority official game.

    void GhostEntity::reset()
    {
        pos_ = spawn_.second;
        ghost_mode_ = ghost_mode::leaving;
        OnEvent(GameEvent::GhostModeChanged, 0);
        auto& random = singleton::Random::get_instance();
        std::vector<Direction> directions = {Direction::Up, Direction::Left, Direction::Down, Direction::Right};
        currentDirection = directions[random.get_int(0,directions.size()-1)];
        lastPossibleDirections = {Direction::None};
        target = spawn_.first;
    }

    float GhostEntity::distance(const Position& position_a, const Position& position_b)
    {
        return std::abs(position_a.x - position_b.x) +
               std::abs(position_a.y - position_b.y);
    }


    bool GhostEntity::changed_directions(const std::vector<Direction>& newDirections) {
        std::unordered_set<Direction> newSet(newDirections.begin(), newDirections.end());

        // Check if we just entered an intersection
        bool enteredIntersection = false;

        if (newSet != lastPossibleDirections) {
            enteredIntersection = true;

        }
        lastPossibleDirections = newSet;

        return enteredIntersection;
    }

    //Blinky

    void BlinkyEntity::chase(const ChaseData& data)
    {
        ghost_mode_ = ghost_mode::chase;
        OnEvent(GameEvent::GhostModeChanged, 0);
        target = data.pacman_pos;
    }

    //Pinky

    void PinkyEntity::chase(const ChaseData& data)
    {
        ghost_mode_ = ghost_mode::chase;
        OnEvent(GameEvent::GhostModeChanged, 0);
        switch (data.pacman_dir)
        {
            case Direction::Up:
                {
                    target.x = data.pacman_pos.x - size_.width * 4; //funny Easter egg. this was a bug in the original game.
                    target.y = data.pacman_pos.y - size_.height * 4;
                    break;
                }
            case Direction::Down: target.y = data.pacman_pos.y + size_.height * 4; break;
            case Direction::Left: target.x = data.pacman_pos.x - size_.width * 4; break;
            case Direction::Right: target.x = data.pacman_pos.x + size_.width * 4; break;
            case Direction::None: target = scatter_corner_; break; //for safety
        }
    }

    //Inky

    void InkyEntity::chase(const ChaseData& data)
    {
        ghost_mode_ = ghost_mode::chase;
        OnEvent(GameEvent::GhostModeChanged, 0);
        Position intermediate = data.pacman_pos;
        switch (data.pacman_dir)
        {
            case Direction::Up:
                {
                    intermediate.x = data.pacman_pos.x - size_.width * 2; //same bug here, just with 2 squares instead of 4
                    intermediate.y = data.pacman_pos.y - size_.height * 2;
                    break;
                }
            case Direction::Down: intermediate.y = data.pacman_pos.y + size_.height * 2; break;
            case Direction::Left: intermediate.x = data.pacman_pos.x - size_.width * 2; break;
            case Direction::Right: intermediate.x = data.pacman_pos.x + size_.width * 2; break;
            case Direction::None: break;
        }
        float dx = intermediate.x - data.blinky_pos.x;
        float dy = intermediate.y - data.blinky_pos.y;

        target.x = intermediate.x + dx;
        target.y = intermediate.y + dy;
    }

    //Clyde

    void ClydeEntity::chase(const ChaseData& data)
    {
        ghost_mode_ = ghost_mode::chase;
        OnEvent(GameEvent::GhostModeChanged, 0);
        if (distance(pos_,data.pacman_pos) < visibility_)
        {
            // target = scatter_corner_;   // this is the official logic but its boring.
            auto& random = singleton::Random::get_instance();
            target = Position{random.get_float(-1,1), random.get_float(-1,1)};
            return;
        }
        target = data.pacman_pos;
    }
} // logic