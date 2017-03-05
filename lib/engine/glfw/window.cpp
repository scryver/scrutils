#include "window.hpp"

#include <cassert>
#include <string>

// #include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "Scryver/Debug/Printer.hpp"

#include "Scryver/Inputs/UserInput.hpp"
#include "Scryver/Inputs/KeyboardCodes.hpp"
#include "Scryver/Math/Vector2D.hpp"

using Scryver::Engine::GLFWWindow;
using Scryver::Math::Vector2D;
using Scryver::Math::Vector2Df;
using namespace Scryver::Keys;

GLFWWindow::GLFWWindow()
    : Scryver::Engine::IWindow()
    , m_window(nullptr)
    , m_userInput(nullptr)
{
    // Empty
}

bool GLFWWindow::initialize(uint16_t width, uint16_t height,
                            const std::string& title)
{
    return initialize(Vector2D<uint16_t>(width, height), title);
}

bool GLFWWindow::initialize(const Vector2D<uint16_t>& size,
                            const std::string& title)
{
    assert(m_window == nullptr && "Window already initialized!");
    assert(m_userInput == nullptr && "User input already initialized!");

    if (!glfwInit())
    {
        errorPrint("Failed to initialize GLFW");
        return false;
    }

    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_SAMPLES, 4);                                // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //We don't want the old OpenGL
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    m_size = size;

    // create the window
    m_window = glfwCreateWindow(m_size.x, m_size.y, title.c_str(), NULL, NULL);

    if( m_window == NULL ){
        errorPrint("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_window);

    glfwSwapInterval(0);

    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetFramebufferSizeCallback(m_window, resizeCallback);

    m_userInput = new Scryver::Inputs::UserInput;

    return m_userInput->initialize(102);
}

void GLFWWindow::destroy()
{
    if (m_userInput != nullptr)
    {
        delete m_userInput;
        m_userInput = nullptr;
    }
    if (m_window != nullptr)
    {
        if (glfwWindowShouldClose(m_window))
            glfwSetWindowShouldClose(m_window, GL_TRUE);
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
    glfwTerminate();
}

void GLFWWindow::size(const Vector2D<uint16_t>& size)
{
    if (m_window == nullptr)
    {
        errorPrint("Window not initialized!");
        return;
    }

    m_size = size;
    glfwSetWindowSize(m_window, m_size.x, m_size.y);
}

void GLFWWindow::width(uint16_t w)
{
    if (m_window == nullptr)
    {
        errorPrint("Window not initialized!");
        return;
    }

    m_size.x = w;
    glfwSetWindowSize(m_window, m_size.x, m_size.y);
}

void GLFWWindow::height(uint16_t h)
{
    if (m_window == nullptr)
    {
        errorPrint("Window not initialized!");
        return;
    }

    m_size.y = h;
    glfwSetWindowSize(m_window, m_size.x, m_size.y);
}

bool GLFWWindow::isOpen() const
{
    return m_window != nullptr && !glfwWindowShouldClose(m_window);
}

void GLFWWindow::pollEvents()
{
    if (m_userInput == nullptr || m_window == nullptr)
        return;

    m_userInput->update();
    glfwPollEvents();

    double x, y;
    glfwGetCursorPos(m_window, &x, &y);
    m_mousePosition.x = static_cast<float>(x);
    m_mousePosition.y = static_cast<float>(y);
}

void GLFWWindow::clear()
{
    if (m_window != nullptr)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLFWWindow::display()
{
    if (m_window != nullptr)
        glfwSwapBuffers(m_window);
}

void GLFWWindow::close()
{
    if (m_window != nullptr)
        glfwSetWindowShouldClose(m_window, GL_TRUE);
}

bool GLFWWindow::isKeyPressed(uint16_t key) const
{
    return m_userInput != nullptr && m_userInput->isKeyPressed(key);
}

bool GLFWWindow::isKeyReleased(uint16_t key) const
{
    return m_userInput != nullptr && m_userInput->isKeyReleased(key);
}

bool GLFWWindow::isKeyDown(uint16_t key) const
{
    return m_userInput != nullptr && m_userInput->isKeyDown(key);
}

bool GLFWWindow::isKeyUp(uint16_t key) const
{
    return m_userInput != nullptr && m_userInput->isKeyUp(key);
}

void GLFWWindow::mousePosition(const Vector2Df& pos)
{
    m_mousePosition = pos;
    glfwSetCursorPos(m_window, static_cast<double>(pos.x), static_cast<double>(pos.y));
}

void GLFWWindow::keyCallback(GLFWwindow* window, int key, int scancode,
                             int action, int mods)
{
    GLFWWindow* w = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS)
        w->m_userInput->pressKey(static_cast<uint16_t>(key));
    else if (action == GLFW_RELEASE)
        w->m_userInput->releaseKey(static_cast<uint16_t>(key));
}

void GLFWWindow::resizeCallback(GLFWwindow* window, int width, int height)
{
    GLFWWindow* w = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
    w->m_size.x = static_cast<uint16_t>(width);
    w->m_size.y = static_cast<uint16_t>(height);
}
