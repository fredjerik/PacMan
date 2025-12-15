#include "PacManView.h"
#include <SFML/Graphics/Rect.hpp>

namespace view
{
    PacManView::PacManView(std::shared_ptr<logic::PacmanEntity> model)
        // Call the base class constructor with the model and the specific texture rect for Pac-Man.
        // We are assuming the top-left sprite at (0,0) with size 16x16 is a Pac-Man.
        : EntityView(model, sf::IntRect(852, 4, 35, 35))
    {
        // The constructor body can be empty for this minimal implementation.
        // Any Pac-Man specific view logic would go here.
    }
} // view
