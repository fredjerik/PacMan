#ifndef PACMAN_COLLECTABLEENTITY_H
#define PACMAN_COLLECTABLEENTITY_H

#include "Entity.h"
namespace logic
{
    enum class CollectableType
    {
        Coin,
        PowerUp,
        Fruit
    };
    class CollectableEntity: public Entity {
    public:
        CollectableEntity(Position pos, Size size) : Entity(pos, size)
        {
            collected = false;
            value = 0;
        }

        ~CollectableEntity() override = default;
        virtual void onCollected()
        {
            collected = true;
            OnEvent(GameEvent::CollectableCollected, value);
            notify();
        }
        void update(float deltaTime) override {}
        virtual CollectableType getType() const = 0;

    protected:
        bool collected;
        int value = 0;
    };

    class Coin : public CollectableEntity {
    public:
        Coin(Position pos) : CollectableEntity(pos, Size{0.3,0.3})
        {
            value = 10;
        }
        CollectableType getType() const override { return CollectableType::Coin; }
    };

    class PowerUp : public CollectableEntity
    {
    public:
        PowerUp(Position pos) : CollectableEntity(pos, Size{0.8,0.8})
        {
            value = 50;
        }
        CollectableType getType() const override { return CollectableType::PowerUp; }
    };

    class Fruit : public CollectableEntity
    {
    public:
        Fruit(Position pos) : CollectableEntity(pos, Size{0.8,0.8})
        {
            value = 100;
        }
        CollectableType getType() const override { return CollectableType::Fruit; }
    };

} // logic

#endif //PACMAN_COLLECTABLEENTITY_H