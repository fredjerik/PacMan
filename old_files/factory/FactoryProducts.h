#ifndef PACMAN_FACTORYPRODUCTS_H
#define PACMAN_FACTORYPRODUCTS_H

#include <memory>

// Forward-declare the base classes
namespace logic { class Entity; }
namespace view { class EntityView; }

namespace factory {

    // This struct holds the products created by a factory method.
    // It contains the model (for the World) and the view (for the LevelState).
    struct EntityProduct {
        std::shared_ptr<logic::Entity> model;
        std::shared_ptr<view::EntityView> view;
    };

}

#endif //PACMAN_FACTORYPRODUCTS_H
