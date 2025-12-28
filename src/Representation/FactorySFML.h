#ifndef PACMAN_FACTORYSFML_H
#define PACMAN_FACTORYSFML_H

#include "Logic/Patterns/AbstractFactory.h"
#include <memory>
#include "../Logic/Entities/Entity.h"
#include "View/EntityView.h"
#include "../Logic/Entities/CollectableEntity.h"
#include "View/ConsumableView.h"

namespace factory
{

    class FactorySFML: public AbstractFactory
    {
    public:
        FactorySFML(std::shared_ptr<logic::Score> score) : AbstractFactory(score){}
        std::shared_ptr<logic::PacmanEntity> create_pacman(logic::Position startPos, float velX_unit, float velY_unit) override;
        std::shared_ptr<logic::Coin> create_coin(logic::Position startPos) override;
        std::shared_ptr<logic::PowerUp> create_powerup(logic::Position startPos) override;
        std::shared_ptr<logic::Fruit> create_fruit(logic::Position startPos) override;
    };
} // factory

#endif //PACMAN_FACTORYSFML_H
