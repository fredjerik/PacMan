#ifndef PACMAN_FACTORYSFML_H
#define PACMAN_FACTORYSFML_H

#include "Logic/Patterns/AbstractFactory.h"
#include <memory>
#include "../Logic/Entities/Entity.h"
#include "View/EntityView.h"

namespace factory
{

    class FactorySFML: public AbstractFactory
    {
    public:
        FactorySFML() = default;
        std::shared_ptr<logic::PacmanEntity> create_pacman(logic::Position startPos, float velX_unit, float velY_unit) override;
    };
} // factory

#endif //PACMAN_FACTORYSFML_H
