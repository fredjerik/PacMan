#include "ConsumableView.h"

#include "Representation/Game.h"

namespace view
{
    CoinView::CoinView(std::weak_ptr<logic::Coin> model)
    : EntityView(model, sf::IntRect(505, 611, 19,19))
    {
        // std::cout << "CoinView initialized!" << std::endl;
    }

    void CoinView::onGameEvent(logic::GameEvent event, int data)
    {

    }

    PowerUpView::PowerUpView(std::weak_ptr<logic::PowerUp> model)
        : EntityView(model, sf::IntRect(527,597,30,30)){}

    void PowerUpView::onGameEvent(logic::GameEvent event, int data){}

    FruitView::FruitView(std::weak_ptr<logic::Fruit> model)
        : EntityView(model, sf::IntRect(602,4,35,35))
    {
        // std::cout << "CoinView initialized!" << std::endl;
    }
    void FruitView::onGameEvent(logic::GameEvent event, int data){}
} // view