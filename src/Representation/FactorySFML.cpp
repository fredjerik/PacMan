#include "../Logic/Entities/Dynamic_Entities/PacmanEntity.h"
#include "View/PacManView.h"

#include "FactorySFML.h"

namespace factory
{
    std::shared_ptr<logic::PacmanEntity> FactorySFML::create_pacman(logic::Position startPos, logic::Size size, float velX_unit, float velY_unit)
    {
        std::shared_ptr<logic::PacmanEntity> model = std::make_shared<logic::PacmanEntity>(startPos, size, velX_unit, velY_unit);
        std::unique_ptr<view::PacManView> view = std::make_unique<view::PacManView>(model);
        model->attach(std::move(view));
        return model;
    }
} // factory
