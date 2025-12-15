#ifndef PACMAN_PACMANVIEW_H
#define PACMAN_PACMANVIEW_H

#include "view/EntityView.h"
#include "../Logic/Entities/Dynamic_Entities/PacmanEntity.h"
#include <memory>

namespace view {

    class PacManView : public EntityView {
    public:
        explicit PacManView(std::shared_ptr<logic::pacman> model, const Camera& camera);

        // update() and draw() are now inherited from EntityView
    };

}

#endif //PACMAN_PACMANVIEW_H
