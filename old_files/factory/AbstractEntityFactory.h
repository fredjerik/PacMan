#ifndef PACMAN_ABSTRACTENTITYFACTORY_H
#define PACMAN_ABSTRACTENTITYFACTORY_H

#include "FactoryProducts.h" // Include the new product definition
#include <memory>

// Forward-declare the classes the factory will create
namespace logic {
    class PacmanEntity;
    class ghost;
}

namespace logic {

    // This is the abstract "contract" for a factory.
    class AbstractEntityFactory {
    public:
        virtual ~AbstractEntityFactory() = default;

        // The factory methods now return an EntityProduct,
        // which contains both the model and the view.
        virtual factory::EntityProduct createPacMan(float x, float y) = 0;
        // virtual factory::EntityProduct createGhost(float x, float y) = 0;
    };

}

#endif //PACMAN_ABSTRACTENTITYFACTORY_H
