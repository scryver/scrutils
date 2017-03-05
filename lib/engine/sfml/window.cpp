#include "window.hpp"

#include <cassert>
#include <string>

// #include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "Scryver/Debug/Printer.hpp"
#include "Scryver/Inputs/UserInput.hpp"
#include "Scryver/Inputs/KeyboardCodes.hpp"
#include "Scryver/Math/Vector2D.hpp"

using Scryver::Engine::SFMLWindow;
using Scryver::Engine::CursorMode;
using Scryver::Math::Vector2D;
using Scryver::Math::Vector2Df;
using namespace Scryver::Keys;

SFMLWindow::SFMLWindow()
    : Scryver::Engine::IWindow()
    , m_window(nullptr)
    , m_userInput(nullptr)
{
    // Empty
}

bool SFMLWindow::initialize(uint16_t width, uint16_t height,
                            const std::string& title, CursorMode cm)
{
    return initialize(Vector2D<uint16_t>(width, height), title, cm);
}

bool SFMLWindow::initialize(const Vector2D<uint16_t>& size,
                            const std::string& title, CursorMode cm)
{
    assert(m_window == nullptr && "Window already initialized!");
    assert(m_userInput == nullptr && "User input already initialized!");

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Debug;

    m_size = size;

    // create the window
    m_window = new sf::Window(sf::VideoMode(m_size.x, m_size.y), title.c_str(), sf::Style::Default, settings);

    m_window->setVerticalSyncEnabled(false);

    cursorMode(cm);

    m_userInput = new Scryver::Inputs::UserInput;

    return m_userInput->initialize(102);
}

void SFMLWindow::destroy()
{
    if (m_userInput != nullptr)
    {
        delete m_userInput;
        m_userInput = nullptr;
    }
    if (m_window != nullptr)
    {
        if (m_window->isOpen())
            m_window->close();
        delete m_window;
        m_window = nullptr;
    }
}

void SFMLWindow::size(const Vector2D<uint16_t>& size)
{
    if (m_window == nullptr)
    {
        errorPrint("Window not initialized!");
        return;
    }

    m_size = size;
    sf::Vector2u s(m_size.x, m_size.y);
    m_window->setSize(s);
}

void SFMLWindow::width(uint16_t w)
{
    if (m_window == nullptr)
    {
        errorPrint("Window not initialized!");
        return;
    }

    m_size.x = w;
    sf::Vector2u s = m_window->getSize();
    s.x = static_cast<unsigned int>(w);
    m_window->setSize(s);
}

void SFMLWindow::height(uint16_t h)
{
    if (m_window == nullptr)
    {
        errorPrint("Window not initialized!");
        return;
    }

    m_size.y = h;
    sf::Vector2u s = m_window->getSize();
    s.y = static_cast<unsigned int>(h);
    m_window->setSize(s);
}

void SFMLWindow::cursorMode(CursorMode cm)
{
    m_cursorMode = cm;
    if (m_cursorMode == CursorMode::Centered)
    {
        m_window->setMouseCursorVisible(false);
        // m_window->setMouseCursorGrabbed(true);
    }
    else if (m_cursorMode == CursorMode::Hidden)
    {
        m_window->setMouseCursorVisible(false);
        // m_window->setMouseCursorGrabbed(false);
    }
    else if (m_cursorMode == CursorMode::Normal)
    {
        m_window->setMouseCursorVisible(true);
        // m_window->setMouseCursorGrabbed(false);
    }
}

bool SFMLWindow::isOpen() const
{
    return m_window != nullptr && m_window->isOpen();
}

bool SFMLWindow::pollEvents()
{
    if (m_userInput == nullptr || m_window == nullptr)
    {
        errorPrint("Window not initialized!");
        return true;
    }

    m_userInput->update();
    sf::Event event;
    bool shouldClose = false;
    while (m_window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            shouldClose = true;
        else if (event.type == sf::Event::Resized)
        {
            m_size.x = static_cast<uint16_t>(event.size.width);
            m_size.y = static_cast<uint16_t>(event.size.height);
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            m_mousePosition.x = static_cast<float>(event.mouseMove.x);
            m_mousePosition.y = static_cast<float>(event.mouseMove.y);

            if (m_cursorMode == CursorMode::Centered)
            {
                m_mousePosition.x -= static_cast<float>(m_size.x) / 2.0f;
                m_mousePosition.y -= static_cast<float>(m_size.y) / 2.0f;
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
                m_userInput->pressKey(Keys::Space);
            else if (event.key.code == sf::Keyboard::A)
                m_userInput->pressKey(Keys::A);
            else if (event.key.code == sf::Keyboard::B)
                m_userInput->pressKey(Keys::B);
            else if (event.key.code == sf::Keyboard::C)
                m_userInput->pressKey(Keys::C);
            else if (event.key.code == sf::Keyboard::D)
                m_userInput->pressKey(Keys::D);
            else if (event.key.code == sf::Keyboard::E)
                m_userInput->pressKey(Keys::E);
            else if (event.key.code == sf::Keyboard::F)
                m_userInput->pressKey(Keys::F);
            else if (event.key.code == sf::Keyboard::G)
                m_userInput->pressKey(Keys::G);
            else if (event.key.code == sf::Keyboard::H)
                m_userInput->pressKey(Keys::H);
            else if (event.key.code == sf::Keyboard::I)
                m_userInput->pressKey(Keys::I);
            else if (event.key.code == sf::Keyboard::J)
                m_userInput->pressKey(Keys::J);
            else if (event.key.code == sf::Keyboard::K)
                m_userInput->pressKey(Keys::K);
            else if (event.key.code == sf::Keyboard::L)
                m_userInput->pressKey(Keys::L);
            else if (event.key.code == sf::Keyboard::M)
                m_userInput->pressKey(Keys::M);
            else if (event.key.code == sf::Keyboard::N)
                m_userInput->pressKey(Keys::N);
            else if (event.key.code == sf::Keyboard::O)
                m_userInput->pressKey(Keys::O);
            else if (event.key.code == sf::Keyboard::P)
                m_userInput->pressKey(Keys::P);
            else if (event.key.code == sf::Keyboard::Q)
                m_userInput->pressKey(Keys::Q);
            else if (event.key.code == sf::Keyboard::R)
                m_userInput->pressKey(Keys::R);
            else if (event.key.code == sf::Keyboard::S)
                m_userInput->pressKey(Keys::S);
            else if (event.key.code == sf::Keyboard::T)
                m_userInput->pressKey(Keys::T);
            else if (event.key.code == sf::Keyboard::U)
                m_userInput->pressKey(Keys::U);
            else if (event.key.code == sf::Keyboard::V)
                m_userInput->pressKey(Keys::V);
            else if (event.key.code == sf::Keyboard::W)
                m_userInput->pressKey(Keys::W);
            else if (event.key.code == sf::Keyboard::X)
                m_userInput->pressKey(Keys::X);
            else if (event.key.code == sf::Keyboard::Y)
                m_userInput->pressKey(Keys::Y);
            else if (event.key.code == sf::Keyboard::Z)
                m_userInput->pressKey(Keys::Z);
            else if (event.key.code == sf::Keyboard::Num1)
                m_userInput->pressKey(Keys::Number_1);
            else if (event.key.code == sf::Keyboard::Num2)
                m_userInput->pressKey(Keys::Number_2);
            else if (event.key.code == sf::Keyboard::Num3)
                m_userInput->pressKey(Keys::Number_3);
            else if (event.key.code == sf::Keyboard::Num4)
                m_userInput->pressKey(Keys::Number_4);
            else if (event.key.code == sf::Keyboard::Num5)
                m_userInput->pressKey(Keys::Number_5);
            else if (event.key.code == sf::Keyboard::Num6)
                m_userInput->pressKey(Keys::Number_6);
            else if (event.key.code == sf::Keyboard::Escape)
                m_userInput->pressKey(Keys::Escape);
            else
                errorPrint("Key " << event.key.code << " is not implemented yet.");
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Space)
                m_userInput->releaseKey(Keys::Space);
            else if (event.key.code == sf::Keyboard::A)
                m_userInput->releaseKey(Keys::A);
            else if (event.key.code == sf::Keyboard::B)
                m_userInput->releaseKey(Keys::B);
            else if (event.key.code == sf::Keyboard::C)
                m_userInput->releaseKey(Keys::C);
            else if (event.key.code == sf::Keyboard::D)
                m_userInput->releaseKey(Keys::D);
            else if (event.key.code == sf::Keyboard::E)
                m_userInput->releaseKey(Keys::E);
            else if (event.key.code == sf::Keyboard::F)
                m_userInput->releaseKey(Keys::F);
            else if (event.key.code == sf::Keyboard::G)
                m_userInput->releaseKey(Keys::G);
            else if (event.key.code == sf::Keyboard::H)
                m_userInput->releaseKey(Keys::H);
            else if (event.key.code == sf::Keyboard::I)
                m_userInput->releaseKey(Keys::I);
            else if (event.key.code == sf::Keyboard::J)
                m_userInput->releaseKey(Keys::J);
            else if (event.key.code == sf::Keyboard::K)
                m_userInput->releaseKey(Keys::K);
            else if (event.key.code == sf::Keyboard::L)
                m_userInput->releaseKey(Keys::L);
            else if (event.key.code == sf::Keyboard::M)
                m_userInput->releaseKey(Keys::M);
            else if (event.key.code == sf::Keyboard::N)
                m_userInput->releaseKey(Keys::N);
            else if (event.key.code == sf::Keyboard::O)
                m_userInput->releaseKey(Keys::O);
            else if (event.key.code == sf::Keyboard::P)
                m_userInput->releaseKey(Keys::P);
            else if (event.key.code == sf::Keyboard::Q)
                m_userInput->releaseKey(Keys::Q);
            else if (event.key.code == sf::Keyboard::R)
                m_userInput->releaseKey(Keys::R);
            else if (event.key.code == sf::Keyboard::S)
                m_userInput->releaseKey(Keys::S);
            else if (event.key.code == sf::Keyboard::T)
                m_userInput->releaseKey(Keys::T);
            else if (event.key.code == sf::Keyboard::U)
                m_userInput->releaseKey(Keys::U);
            else if (event.key.code == sf::Keyboard::V)
                m_userInput->releaseKey(Keys::V);
            else if (event.key.code == sf::Keyboard::W)
                m_userInput->releaseKey(Keys::W);
            else if (event.key.code == sf::Keyboard::X)
                m_userInput->releaseKey(Keys::X);
            else if (event.key.code == sf::Keyboard::Y)
                m_userInput->releaseKey(Keys::Y);
            else if (event.key.code == sf::Keyboard::Z)
                m_userInput->releaseKey(Keys::Z);
            else if (event.key.code == sf::Keyboard::Num1)
                m_userInput->releaseKey(Keys::Number_1);
            else if (event.key.code == sf::Keyboard::Num2)
                m_userInput->releaseKey(Keys::Number_2);
            else if (event.key.code == sf::Keyboard::Num3)
                m_userInput->releaseKey(Keys::Number_3);
            else if (event.key.code == sf::Keyboard::Num4)
                m_userInput->releaseKey(Keys::Number_4);
            else if (event.key.code == sf::Keyboard::Num5)
                m_userInput->releaseKey(Keys::Number_5);
            else if (event.key.code == sf::Keyboard::Num6)
                m_userInput->releaseKey(Keys::Number_6);
            else if (event.key.code == sf::Keyboard::Escape)
                m_userInput->releaseKey(Keys::Escape);
            else
                errorPrint("Key " << event.key.code << " is not implemented yet.");
        }
    }

    if (m_cursorMode == CursorMode::Centered)
    {
        sf::Mouse::setPosition(sf::Vector2i(static_cast<int>((m_size.x / 2)),
                                            static_cast<int>((m_size.y / 2))),
                               *m_window);
    }

    return shouldClose;
}

void SFMLWindow::clear()
{
    if (m_window != nullptr)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SFMLWindow::display()
{
    if (m_window != nullptr)
        m_window->display();
}

void SFMLWindow::close()
{
    if (m_window != nullptr)
        m_window->close();
}

bool SFMLWindow::isKeyPressed(uint16_t key) const
{
    return m_userInput != nullptr && m_userInput->isKeyPressed(key);
}

bool SFMLWindow::isKeyReleased(uint16_t key) const
{
    return m_userInput != nullptr && m_userInput->isKeyReleased(key);
}

bool SFMLWindow::isKeyDown(uint16_t key) const
{
    return m_userInput != nullptr && m_userInput->isKeyDown(key);
}

bool SFMLWindow::isKeyUp(uint16_t key) const
{
    return m_userInput != nullptr && m_userInput->isKeyUp(key);
}

void SFMLWindow::mousePosition(const Vector2Df& pos)
{
    if (m_window == nullptr)
        return;

    m_mousePosition = pos;
    sf::Mouse::setPosition(sf::Vector2i(static_cast<int>(m_mousePosition.x),
                                        static_cast<int>(m_mousePosition.y)),
                           *m_window);
}
