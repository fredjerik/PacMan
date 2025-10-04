#ifndef PACMAN_SFMLRENDERER_H
#define PACMAN_SFMLRENDERER_H

#include "../../Logic/Patterns/Renderer.h"
#include "../Camera.h"

namespace representation {

    /**
     * @brief The concrete implementation of the Renderer interface.
     *
     * This class acts as a "toolbox" that inherits from the generic logic::Renderer
     * but also holds references to all the representation-specific tools needed
     * for drawing, like the Camera.
     */
    class SFMLRenderer : public logic::Renderer {
    public:
        // Constructor takes all the tools the views will need
        explicit SFMLRenderer(Camera& cam) : m_camera(cam) {}

        // Getter for the Camera tool
        Camera& getCamera() { return m_camera; }

    private:
        Camera& m_camera;
    };

} // namespace representation

#endif //PACMAN_SFMLRENDERER_H
