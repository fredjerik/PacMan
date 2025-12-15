#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include "DynamicEntity.h"

namespace logic {

    class PacmanEntity : public DynamicEntity {
    public:
        explicit PacmanEntity(Position startPos, Size size, float velX_unit, float velY_unit);


        int getLives() const { return lives; }
        void loseLife();

    private:
        int lives;
        Position startPos;
    };

} // namespace Logic

#endif //PACMAN_PACMAN_H

