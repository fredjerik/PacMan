#include "PacManView.h"

namespace view {

    PacManView::PacManView(std::shared_ptr<logic::pacman> model, const Camera& camera)
        // Call the base class constructor with the specific texture rect for Pac-Man
        : EntityView(model, camera, sf::IntRect(852, 4, 35,35)){
        // The base class constructor handles everything else.
    }

    // update() and draw() are now handled by the EntityView base class.

}