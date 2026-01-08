#include "PacmanEntity.h"

namespace logic {

    PacmanEntity::PacmanEntity(Position startPos, float velX_unit, float velY_unit)
        : DynamicEntity(startPos, Size{1,1},velX_unit, velY_unit, 4.0f), startPos(startPos) {
        lives = 3;
    }

    void PacmanEntity::loseLife() {
        lives--;
        std::cout << "PacmanEntity: Lost life. Lives left: " << lives << std::endl;
        OnEvent(GameEvent::PacmanDied, 1); // This should trigger the animation
        notify();
    }

} // namespace Logic