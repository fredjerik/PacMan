#include "PacmanEntity.h"

namespace logic {
    void PacmanEntity::loseLife() {
        lives--;
        std::cout << "PacmanEntity: Lost life. Lives left: " << lives << std::endl;
        OnEvent(GameEvent::PacmanDied, 1);
        notify();
    }

    PacmanEntity::PacmanEntity(Position startPos, Size tile_size)
        : DynamicEntity(startPos, Size{1,1}, tile_size, 4.0f), startPos(startPos) {
        lives = 3;
    }
} // namespace Logic