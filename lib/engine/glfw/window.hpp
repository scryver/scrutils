#ifndef SCRYVER_ENGINE_GLFW_WINDOW_HPP
#define SCRYVER_ENGINE_GLFW_WINDOW_HPP

#include <cstdint>
#include <string>

#include "../iwindow.hpp"

struct GLFWwindow;

namespace Scryver {

namespace Inputs {
    class UserInput;
}

namespace Engine {

class GLFWWindow : public IWindow
{
public:
    GLFWWindow();
    ~GLFWWindow() { destroy(); }
    bool initialize(uint16_t width = 800, uint16_t height = 600,
                    const std::string& title = "GLFW Window");
    void destroy();

    bool isOpen()                       const;
    void pollEvents();
    void clear();
    void display();
    void close();

    bool isKeyPressed(uint16_t key)     const;
    bool isKeyReleased(uint16_t key)    const;
    bool isKeyDown(uint16_t key)        const;
    bool isKeyUp(uint16_t key)          const;

private:
    GLFWwindow*             m_window;
    Inputs::UserInput*      m_userInput;

    static void keyCallback(GLFWwindow* window, int key, int scancode,
                            int action, int mods);
};

}  // namespace Engine

}  // namespace Scryver

#endif  // SCRYVER_ENGINE_GLFW_WINDOW_HPP
