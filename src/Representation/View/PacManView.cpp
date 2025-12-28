#include "PacManView.h"
#include <SFML/Graphics/Rect.hpp>

namespace view
{
    PacManView::PacManView(std::weak_ptr<logic::PacmanEntity> model) //
        : EntityView(model, sf::IntRect(852, 4, 35, 35)){}

    void PacManView::onGameEvent(logic::GameEvent event, int data)
    {
        switch (event)
        {
            case logic::GameEvent::PacmanDied: break ;
        }
    }
} // view
