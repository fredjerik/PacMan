#ifndef PACMAN_ABSTRACTFACTORY_H
#define PACMAN_ABSTRACTFACTORY_H

#include <memory>
#include "../Entities/Dynamic_Entities/PacmanEntity.h"

namespace factory
{
    class AbstractFactory
    {
    public:
        AbstractFactory() = default;
        virtual ~AbstractFactory() = default;
        virtual std::shared_ptr<logic::PacmanEntity> create_pacman(logic::Position startPos, logic::Size size, float velX_unit, float velY_unit) = 0;
    };
} // factory

#endif //PACMAN_ABSTRACTFACTORY_H