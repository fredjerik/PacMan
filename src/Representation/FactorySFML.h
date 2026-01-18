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
        std::shared_ptr<logic::PacmanEntity> create_pacman(logic::Position startPos, logic::Size tile_size) override;
        std::shared_ptr<logic::Coin> create_coin(logic::Position startPos, logic::Size tile_size) override;
        std::shared_ptr<logic::PowerUp> create_powerup(logic::Position startPos, logic::Size tile_size) override;
        std::shared_ptr<logic::Fruit> create_fruit(logic::Position startPos, logic::Size tile_size) override;
        std::shared_ptr<logic::BlinkyEntity> create_blinky(const std::vector<logic::Position>& ghost_house,
            const std::vector<logic::Position>& ghost_gate, logic::Size tile_size) override;
        std::shared_ptr<logic::PinkyEntity> create_pinky(const std::vector<logic::Position>& ghost_house,
            const std::vector<logic::Position>& ghost_gate, logic::Size tile_size) override;
        std::shared_ptr<logic::InkyEntity> create_inky(const std::vector<logic::Position>& ghost_house,
            const std::vector<logic::Position>& ghost_gate, logic::Size tile_size) override;
        std::shared_ptr<logic::ClydeEntity> create_clyde(const std::vector<logic::Position>& ghost_house,
            const std::vector<logic::Position>& ghost_gate, logic::Size tile_size) override;

    };
} // factory

#endif //PACMAN_FACTORYSFML_H
