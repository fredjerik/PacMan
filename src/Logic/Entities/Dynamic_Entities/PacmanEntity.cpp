#include "PacmanEntity.h"


namespace logic {

    PacmanEntity::PacmanEntity(Position startPos, Size size, float velX_unit, float velY_unit)
        : DynamicEntity(startPos, size, velX_unit, velY_unit), startPos(startPos) {
        lives = 3;
        speed = 3.0f;
    }

    void PacmanEntity::loseLife() {
        lives--;
        pos = startPos;
        notify();
    }

} // namespace Logic
