#include "SFMLEntityFactory.h"
#include "../../Logic/Entities/Dynamic_Entities/PacmanEntity.h"
#include "../PacManView.h"

namespace view {

    SFMLEntityFactory::SFMLEntityFactory(const Camera& camera) : camera(camera) {}

    factory::EntityProduct SFMLEntityFactory::createPacMan(float x, float y) {
        // 1. Create the Model ("Brains")
        auto model = std::make_shared<logic::PacmanEntity>(logic::Position{x, y});

        // 2. Create the View ("Artist")
        auto view = std::make_shared<view::PacManView>(model, camera);

        // 3. Link them: The View observes the Model
        model->addObserver(view);

        // 4. Return both products
        return {model, view};
    }

}
