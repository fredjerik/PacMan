#ifndef PACMAN_OBSERVER_H
#define PACMAN_OBSERVER_H

#include "Renderer.h"

namespace logic {
    enum class GameEvent {
        None,
        CollectableCollected,
        GhostModeChanged,
        GhostEaten,
        PacmanDied,
        DirectionChanged
    };

    class Observer {
    public:
        virtual ~Observer() = default;

        virtual void update() = 0;

        virtual void onGameEvent(GameEvent event, int data) = 0;

        virtual void draw(Renderer& renderer) = 0;
    };
}

#endif //PACMAN_OBSERVER_H