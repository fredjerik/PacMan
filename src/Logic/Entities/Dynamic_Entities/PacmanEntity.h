#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include <iostream>

#include "DynamicEntity.h"

namespace logic {

    class PacmanEntity : public DynamicEntity {
    public:
        PacmanEntity(Position startPos, Size tile_size);

        int getLives() const { return lives; }
        void loseLife();
        void reset() override
        {
            pos_ = startPos;
            currentDirection = Direction::Right;
            nextDirection = Direction::Right;
            OnEvent(GameEvent::DirectionChanged, static_cast<int>(currentDirection));
        }

    private:
        int lives;
        Position startPos;
    };

} // namespace Logic

#endif //PACMAN_PACMAN_H

