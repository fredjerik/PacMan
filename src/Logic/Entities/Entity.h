#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H

#include "../Patterns/Subject.h"

namespace logic {

    struct Position {
        float x = 0.0f;
        float y = 0.0f;

        bool operator<(const Position& other) const {
            if (x < other.x) return true;
            if (x > other.x) return false;
            return y < other.y;
        }
    };

    struct Size {
        float width = 0.0f;
        float height = 0.0f;
    };

    class Entity: public Subject {
    public:
        explicit Entity(Position startPos, Size size, Size tile_size) : pos_(startPos), size_(size), tile_size_(tile_size) {}
        ~Entity() override = default;

        virtual void update(float deltaTime) = 0;

        [[nodiscard]] Position getPosition() const { return pos_; }
        [[nodiscard]] Size getSize() const { return size_; }

    protected:
        Position pos_;
        Size size_;
        Size tile_size_;
        // right:
    };

} // namespace logic

#endif //PACMAN_ENTITY_H
