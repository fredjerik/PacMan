#include "../Logic/Entities/Dynamic_Entities/PacmanEntity.h"
#include "View/PacManView.h"

#include "FactorySFML.h"

namespace factory
{
    std::shared_ptr<logic::PacmanEntity> FactorySFML::create_pacman(logic::Position startPos, float velX_unit, float velY_unit)
    {
        std::shared_ptr<logic::PacmanEntity> model = std::make_shared<logic::PacmanEntity>(startPos, velX_unit, velY_unit);
        std::shared_ptr<view::PacManView> view = std::make_shared<view::PacManView>(model);
        model->attach(std::move(view));
        attach_score(model);
        return model;
    }

    std::shared_ptr<logic::Coin> FactorySFML::create_coin(logic::Position startPos)
    {
        std::shared_ptr<logic::Coin> model = std::make_shared<logic::Coin>(startPos);
        std::shared_ptr<view::CoinView> view = std::make_shared<view::CoinView>(model);
        model->attach(std::move(view));
        attach_score(model);
        return model;
    }
    std::shared_ptr<logic::PowerUp> FactorySFML::create_powerup(logic::Position startPos)
    {
        std::shared_ptr<logic::PowerUp> model = std::make_shared<logic::PowerUp>(startPos);
        std::shared_ptr<view::PowerUpView> view = std::make_shared<view::PowerUpView>(model);
        model->attach(std::move(view));
        attach_score(model);
        return model;
    }
    std::shared_ptr<logic::Fruit> FactorySFML::create_fruit(logic::Position startPos)
    {
        std::shared_ptr<logic::Fruit> model = std::make_shared<logic::Fruit>(startPos);
        std::shared_ptr<view::FruitView> view = std::make_shared<view::FruitView>(model);
        model->attach(std::move(view));
        attach_score(model);
        return model;
    }
} // factory
