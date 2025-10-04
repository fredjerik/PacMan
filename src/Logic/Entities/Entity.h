#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H

#include "../Patterns/Subject.h"

namespace logic {

    // Using simple structs to avoid SFML dependencies
    struct Position {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct Size {
        float width = 0.0f;
        float height = 0.0f;
    };

    class Entity: public Subject {
    public:
        explicit Entity(Position startPos) : pos(startPos) {}
        virtual ~Entity() = default;

        virtual void update(float deltaTime) = 0;

        Position getPosition() const { return pos; }

    protected:
        Position pos;
    };

} // namespace logic

#endif //PACMAN_ENTITY_H
