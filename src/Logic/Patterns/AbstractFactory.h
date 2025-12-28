#ifndef PACMAN_ABSTRACTFACTORY_H
#define PACMAN_ABSTRACTFACTORY_H

#include <memory>
#include "../Entities/Dynamic_Entities/PacmanEntity.h"
    #include "../../Representation/View/Score.h"
#include "Logic/Entities/CollectableEntity.h"

namespace factory
{
    class AbstractFactory
    {
    public:
        AbstractFactory(std::shared_ptr<logic::Score> score_) : score(score_) {};
        virtual ~AbstractFactory() = default;
        virtual std::shared_ptr<logic::PacmanEntity> create_pacman(logic::Position startPos, float velX_unit, float velY_unit) = 0;
        virtual std::shared_ptr<logic::Coin> create_coin(logic::Position startPos) = 0;
        virtual std::shared_ptr<logic::PowerUp> create_powerup(logic::Position startPos) = 0;
        virtual std::shared_ptr<logic::Fruit> create_fruit(logic::Position startPos) = 0;

    protected:
        void attach_score(std::shared_ptr<logic::Entity> entity)
        {
            entity->attach(score);
        }

    private:
        std::shared_ptr<logic::Score> score;
    };
} // factory

#endif //PACMAN_ABSTRACTFACTORY_H