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
    using IWindow::size;
    using IWindow::width;
    using IWindow::height;
    using IWindow::cursorMode;
    using IWindow::mousePosition;

    GLFWWindow();
    ~GLFWWindow() { destroy(); }
    bool initialize(uint16_t width = 800, uint16_t height = 600,
                    const std::string& title = "GLFW Window",
                    CursorMode cm = CursorMode::Normal) override;
    bool initialize(const Math::Vector2D<uint16_t>& size,
                    const std::string& title = "GLFW Window",
                    CursorMode cm = CursorMode::Normal) override;
    void destroy() override;

    void size(const Math::Vector2D<uint16_t>& size) override;
    void width(uint16_t w) override;
    void height(uint16_t h) override;

    void cursorMode(CursorMode cm) override;

    bool isOpen()                       const override;
    bool pollEvents() override;
    void clear() override;
    void display() override;
    void close() override;

    bool isKeyPressed(uint16_t key)     const override;
    bool isKeyReleased(uint16_t key)    const override;
    bool isKeyDown(uint16_t key)        const override;
    bool isKeyUp(uint16_t key)          const override;

    void mousePosition(const Math::Vector2Df& pos) override;

private:
    GLFWwindow*             m_window;
    Inputs::UserInput*      m_userInput;

    static void keyCallback(GLFWwindow* window, int key, int scancode,
                            int action, int mods);
    static void resizeCallback(GLFWwindow* window, int width, int height);
    // static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
};

}  // namespace Engine

}  // namespace Scryver

#endif  // SCRYVER_ENGINE_GLFW_WINDOW_HPP
