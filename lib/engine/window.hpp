#ifndef SCRYVER_ENGINE_WINDOW_HPP
#define SCRYVER_ENGINE_WINDOW_HPP

#if defined(USING_SFML)
#include "Sfml/window.hpp"
#elif defined(USING_GLFW)
#include "Glfw/window.hpp"
#else
#error "Scryver::Engine::Window has no backend!"
#endif

namespace Scryver {

namespace Engine {

#if defined(USING_SFML)
typedef SFMLWindow Window;
#elif defined(USING_GLFW)
typedef GLFWWindow Window;
#endif

}  // namespace Engine

}  // namespace Scryver

#endif  // SCRYVER_ENGINE_WINDOW_HPP
