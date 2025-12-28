#ifndef PACMAN_PACMANVIEW_H
#define PACMAN_PACMANVIEW_H

#include "EntityView.h"
#include <memory>
#include "Logic/Entities/Dynamic_Entities/PacmanEntity.h"

namespace logic { class Entity; } // Forward declaration

namespace view
{
    class PacManView : public EntityView
    {
    public:
        explicit PacManView(std::weak_ptr<logic::PacmanEntity> model);
        void onGameEvent(logic::GameEvent event, int data) override;
    };
} // view

#endif //PACMAN_PACMANVIEW_H
