#include "window.hpp"

#include <cassert>
#include <string>

// #include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "Scryver/Inputs/UserInput.hpp"
#include "Scryver/Inputs/KeyboardCodes.hpp"

using Scryver::Engine::SFMLWindow;
using namespace Scryver::Keys;

SFMLWindow::SFMLWindow()
    : m_window(nullptr)
    , m_userInput(nullptr)
{
    // Empty
}

bool SFMLWindow::initialize(uint16_t width, uint16_t height,
                            const std::string& title)
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

    // create the window
    m_window = new sf::Window(sf::VideoMode(width, height), title.c_str(), sf::Style::Default, settings);

    // glewExperimental = GL_TRUE;
    // if (glewInit() != GLEW_OK) {
    //     // @TODO: Create a report system
    //     // std::cout << "Failed to initialize GLEW!" << std::endl;
    //     return false;
    // }

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

bool SFMLWindow::isOpen() const
{
    return m_window != nullptr && m_window->isOpen();
}

void SFMLWindow::pollEvents()
{
    if (m_userInput == nullptr || m_window == nullptr)
        return;

    m_userInput->update();
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            m_window->close();
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
                m_userInput->pressKey(Keys::Space);
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
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Space)
                m_userInput->releaseKey(Keys::Space);
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
        }
    }
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
