#include "PacmanEntity.h"


namespace logic {

    PacmanEntity::PacmanEntity(Position startPos, float velX_unit, float velY_unit)
        : DynamicEntity(startPos, velX_unit, velY_unit) {
        lives = 3;
        speed = 3.0f;
    }

    void PacmanEntity::loseLife() {
        lives--;
        pos = startPos;
        notify();
    }

} // namespace Logic
