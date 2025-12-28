#ifndef PACMAN_CONSUMABLEVIEW_H
#define PACMAN_CONSUMABLEVIEW_H

#include "EntityView.h"
#include "Logic/Entities/CollectableEntity.h"

namespace view
{
    class CoinView: public EntityView
    {
    public:
        CoinView(std::weak_ptr<logic::Coin> model);
        void onGameEvent(logic::GameEvent event, int data) override;
    };
    class PowerUpView: public EntityView
    {
    public:
        PowerUpView(std::weak_ptr<logic::PowerUp> model);
        void onGameEvent(logic::GameEvent event, int data) override;
    };
    class FruitView: public EntityView
    {
    public:
        FruitView(std::weak_ptr<logic::Fruit> model);
        void onGameEvent(logic::GameEvent event, int data) override;
    };
} // view

#endif //PACMAN_CONSUMABLEVIEW_H