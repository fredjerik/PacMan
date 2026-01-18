#include "../Logic/Entities/Dynamic_Entities/PacmanEntity.h"
#include "View/PacManView.h"

#include "FactorySFML.h"

#include "View/GhostView.h"

namespace factory
{
    std::shared_ptr<logic::PacmanEntity> FactorySFML::create_pacman(logic::Position startPos, logic::Size tile_size)
    {
        std::shared_ptr<logic::PacmanEntity> model = std::make_shared<logic::PacmanEntity>(startPos, tile_size);
        std::shared_ptr<view::PacManView> view = std::make_shared<view::PacManView>(model);
        model->attach(std::move(view));
        attach_score(model);
        return model;
    }

    std::shared_ptr<logic::Coin> FactorySFML::create_coin(logic::Position startPos, logic::Size tile_size)
    {
        std::shared_ptr<logic::Coin> model = std::make_shared<logic::Coin>(startPos, tile_size);
        std::shared_ptr<view::CoinView> view = std::make_shared<view::CoinView>(model);
        model->attach(std::move(view));
        attach_score(model);
        return model;
    }
    std::shared_ptr<logic::PowerUp> FactorySFML::create_powerup(logic::Position startPos, logic::Size tile_size)
    {
        std::shared_ptr<logic::PowerUp> model = std::make_shared<logic::PowerUp>(startPos, tile_size);
        std::shared_ptr<view::PowerUpView> view = std::make_shared<view::PowerUpView>(model);
        model->attach(std::move(view));
        attach_score(model);
        return model;
    }
    std::shared_ptr<logic::Fruit> FactorySFML::create_fruit(logic::Position startPos, logic::Size tile_size)
    {
        std::shared_ptr<logic::Fruit> model = std::make_shared<logic::Fruit>(startPos, tile_size);
        std::shared_ptr<view::FruitView> view = std::make_shared<view::FruitView>(model);
        model->attach(std::move(view));
        attach_score(model);
        return model;
    }
    std::shared_ptr<logic::BlinkyEntity> FactorySFML::create_blinky(const std::vector<logic::Position>& ghost_house,
            const std::vector<logic::Position>& ghost_gate, logic::Size tile_size)
    {
        std::shared_ptr<logic::BlinkyEntity> model = std::make_shared<logic::BlinkyEntity>(ghost_house, ghost_gate, tile_size);
        std::shared_ptr<view::BlinkyView> view = std::make_shared<view::BlinkyView>(model);
        model->attach(std::move(view));
        attach_score(model);
        return model;
    }
    std::shared_ptr<logic::PinkyEntity> FactorySFML::create_pinky(const std::vector<logic::Position>& ghost_house,
        const std::vector<logic::Position>& ghost_gate, logic::Size tile_size)
    {
        std::shared_ptr<logic::PinkyEntity> model = std::make_shared<logic::PinkyEntity>(ghost_house, ghost_gate, tile_size);
        std::shared_ptr<view::PinkyView> view = std::make_shared<view::PinkyView>(model);
        model->attach(std::move(view));
        attach_score(model);
        return model;
    }
    std::shared_ptr<logic::InkyEntity> FactorySFML::create_inky(const std::vector<logic::Position>& ghost_house,
    const std::vector<logic::Position>& ghost_gate, logic::Size tile_size)
    {
        std::shared_ptr<logic::InkyEntity> model = std::make_shared<logic::InkyEntity>(ghost_house, ghost_gate, tile_size);
        std::shared_ptr<view::InkyView> view = std::make_shared<view::InkyView>(model);
        model->attach(std::move(view));
        attach_score(model);
        return model;
    }
    std::shared_ptr<logic::ClydeEntity> FactorySFML::create_clyde(const std::vector<logic::Position>& ghost_house,
    const std::vector<logic::Position>& ghost_gate, logic::Size tile_size)
    {
        std::shared_ptr<logic::ClydeEntity> model = std::make_shared<logic::ClydeEntity>(ghost_house, ghost_gate, tile_size);
        std::shared_ptr<view::ClydeView> view = std::make_shared<view::ClydeView>(model);
        model->attach(std::move(view));
        attach_score(model);
        return model;
    }
} // factory
