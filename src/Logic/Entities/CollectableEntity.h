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
        CollectableEntity(Position pos, Size size, Size tile_size) : Entity(pos, size, tile_size)
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
        [[nodiscard]] virtual CollectableType getType() const = 0;

    protected:
        bool collected;
        int value = 0;
    };

    class Coin : public CollectableEntity {
    public:
        Coin(Position pos, Size tile_size) : CollectableEntity(pos, Size{0.3,0.3}, tile_size)
        {
            value = 10;
        }
        [[nodiscard]] CollectableType getType() const override { return CollectableType::Coin; }
    };

    class PowerUp : public CollectableEntity
    {
    public:
        PowerUp(Position pos, Size tile_size) : CollectableEntity(pos, Size{0.8,0.8}, tile_size)
        {
            value = 50;
        }
        [[nodiscard]] CollectableType getType() const override { return CollectableType::PowerUp; }
    };

    class Fruit : public CollectableEntity
    {
    public:
        Fruit(Position pos, Size tile_size) : CollectableEntity(pos, Size{0.8,0.8}, tile_size)
        {
            value = 100;
        }
        [[nodiscard]] CollectableType getType() const override { return CollectableType::Fruit; }
    };

} // logic

#endif //PACMAN_COLLECTABLEENTITY_H