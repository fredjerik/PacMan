#include "PacmanEntity.h"


namespace logic {

    PacmanEntity::PacmanEntity(Position startPos, float velX_unit, float velY_unit)
        : DynamicEntity(startPos, Size{1,1},velX_unit, velY_unit) {
        lives = 3;
        speed = 3.0f;
    }

    void PacmanEntity::loseLife() {
        lives--;
        pos_ = startPos;
        notify();
    }

} // namespace Logic
