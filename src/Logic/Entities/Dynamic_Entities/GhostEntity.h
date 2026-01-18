#ifndef PACMAN_GHOSTENTITY_H
#define PACMAN_GHOSTENTITY_H
#include <iostream>
#include <unordered_set>

#include "DynamicEntity.h"

namespace logic
{
    enum class ghost_mode
    {
        chase,
        scatter,
        fear,
        flashing,
        eaten,
        entering,
        leaving,
        spawn
    };

    enum class ghost_type
    {
        Blinky,
        Pinky,
        Inky,
        Clyde
    };

    struct ChaseData {
        Position pacman_pos;
        Direction pacman_dir = Direction::None;
        Position blinky_pos;
    };



    class GhostEntity : public DynamicEntity
    {
    public:
        const float EPSILON = tile_size_.width * 0.1f;

        static std::string to_string(ghost_mode ghost_mode)
        {
            switch (ghost_mode)
            {
            case ghost_mode::chase:
                return "chase";
            case ghost_mode::scatter:
                return "scatter";
            case ghost_mode::fear:
                return "fear";
            case ghost_mode::eaten:
                return "eaten";
            case ghost_mode::entering:
                return "entering";
            case ghost_mode::leaving:
                return "leaving";
            case ghost_mode::spawn:
                return "spawn";
            }
            return "error";
        }

        GhostEntity(ghost_type ghost_type, const std::vector<Position>& ghost_house,
                                 const std::vector<Position>& ghost_gate,
                                 Position scatter_position, Size tile_size);
        void calculate_direction(const std::vector<Direction>& possible_directions);
        bool shouldAllowReverse() const;
        void update(float deltaTime) override;
        void leave_house() {ghost_mode_ = ghost_mode::leaving;};
        static Position findClosestHousePosition(const Position& gate_pos, const std::vector<Position>& ghost_house);

        void chase() {
            ghost_mode_ = ghost_mode::chase;
            OnEvent(GameEvent::GhostModeChanged, 0);
        }
        virtual void update_chase_target(const ChaseData& data) = 0;// all logic from https://www.youtube.com/watch?v=ataGotQ7ir8&t=681s
        void fear(const Position& pacman_position);
        void low_fear() {OnEvent(GameEvent::GhostModeChanged, 2);}
        void eaten();
        void scatter();
        void return_from_fear();
        bool changed_directions(const std::vector<Direction>& newDirections);
        void set_visibility(const float visibility) {visibility_ = size_.width * visibility;}
        ghost_type get_ghost_type() {return ghost_type_;}
        ghost_mode get_ghost_mode() {return ghost_mode_;}

        void set_score_power(const int& score_power) {score_power_ = score_power;}
        void reset() override;
        static float distance(const Position& position_a, const Position& position_b);

    private:
        std::unordered_set<Direction> lastPossibleDirections;

    protected:
        std::vector<Position> ghost_house_;
        std::vector<Position> ghost_gate_;
        ghost_type ghost_type_;
        // static float euclideanDistance(const Position& position_a, const Position& position_b);
        static Position random();

        float visibility_ = 8.0f * size_.width;
        ghost_mode ghost_mode_;
        ghost_mode mode_before_fear_;
        Position target;
        std::pair<Position, Position> spawn_; // first is entrance, second is actual spawn.
        Position scatter_corner_;
        int score_power_ = 1; //200 ** score_multiplier
    };

    class BlinkyEntity : public GhostEntity
    {
    public:
        BlinkyEntity(const std::vector<Position>& ghost_house,
                             const std::vector<Position>& ghost_gate,
                             Size tile_size)
            : GhostEntity(ghost_type::Blinky, ghost_house, ghost_gate, Position{1, -1}, tile_size){}

        void update_chase_target(const ChaseData& data) override;
    };

    class PinkyEntity : public GhostEntity
    {
    public:
        PinkyEntity(const std::vector<Position>& ghost_house,
                             const std::vector<Position>& ghost_gate,
                             Size tile_size)
            : GhostEntity(ghost_type::Pinky, ghost_house, ghost_gate, Position{-1, -1}, tile_size){}

        void update_chase_target(const ChaseData& data) override;
    };

    class InkyEntity : public GhostEntity
    {
    public:
        InkyEntity(const std::vector<Position>& ghost_house,
                             const std::vector<Position>& ghost_gate,
                             Size tile_size)
            : GhostEntity(ghost_type::Inky, ghost_house, ghost_gate, Position{1, 1}, tile_size){}

        void update_chase_target(const ChaseData& data) override;
    };

    class ClydeEntity : public GhostEntity
    {
    public:
        ClydeEntity(const std::vector<Position>& ghost_house,
                             const std::vector<Position>& ghost_gate,
                             Size tile_size)
            : GhostEntity(ghost_type::Clyde, ghost_house, ghost_gate, Position{-1, 1}, tile_size){}

        void update_chase_target(const ChaseData& data) override;
    };
} // logic

#endif //PACMAN_GHOSTENTITY_H