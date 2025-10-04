#ifndef PACMAN_RENDERER_H
#define PACMAN_RENDERER_H

namespace logic {

    /**
     * @brief An empty, abstract interface for a Renderer.
     *
     * This class serves as a generic, transportable object that can be passed from the
     * representation layer through the logic layer without creating a dependency.
     * The concrete renderer in the representation layer will inherit from this and
     * hold the actual rendering tools (like the Camera).
     */
    class Renderer {
    public:
        virtual ~Renderer() = default;
    };

} // namespace logic

#endif //PACMAN_RENDERER_H
