#ifndef PACMAN_SMLENTITYFACTORY_H
#define PACMAN_SMLENTITYFACTORY_H

#include "Logic/factory/AbstractEntityFactory.h"

// Forward-declare the camera, which this factory will need to create views
namespace view {
    class Camera;
}

namespace view {

    // This is the concrete factory for the SFML representation.
    class SFMLEntityFactory : public logic::AbstractEntityFactory {
    public:
        explicit SFMLEntityFactory(const Camera& camera);

        // Override the abstract method to provide a concrete implementation
        factory::EntityProduct createPacMan(float x, float y) override;

    private:
        const Camera& camera; // Needs a camera to create views
    };

}

#endif //PACMAN_SMLENTITYFACTORY_H
