#ifndef PACMAN_ABSTRACTFACTORY_H
#define PACMAN_ABSTRACTFACTORY_H

#include <memory>
#include "../Entities/Dynamic_Entities/PacmanEntity.h"
    #include "../../Representation/View/Score.h"
#include "Logic/Entities/CollectableEntity.h"
#include "Logic/Entities/Dynamic_Entities/GhostEntity.h"

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

        virtual std::shared_ptr<logic::BlinkyEntity> create_blinky(const std::vector<logic::Position>& ghost_house,
            const std::vector<logic::Position>& ghost_gate, float velX_unit, float velY_unit) = 0;
        virtual std::shared_ptr<logic::PinkyEntity> create_pinky(const std::vector<logic::Position>& ghost_house,
            const std::vector<logic::Position>& ghost_gate, float velX_unit, float velY_unit) = 0;
        virtual std::shared_ptr<logic::InkyEntity> create_inky(const std::vector<logic::Position>& ghost_house,
            const std::vector<logic::Position>& ghost_gate, float velX_unit, float velY_unit) = 0;
        virtual std::shared_ptr<logic::ClydeEntity> create_clyde(const std::vector<logic::Position>& ghost_house,
            const std::vector<logic::Position>& ghost_gate, float velX_unit, float velY_unit) = 0;


    protected:
        void attach_score(const std::shared_ptr<logic::Entity>& entity)
        {
            entity->attach(score);
        }

    private:
        std::shared_ptr<logic::Score> score;
    };
} // factory

#endif //PACMAN_ABSTRACTFACTORY_H