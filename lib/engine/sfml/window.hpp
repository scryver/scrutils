#ifndef SCRYVER_ENGINE_SFML_WINDOW_HPP
#define SCRYVER_ENGINE_SFML_WINDOW_HPP

#include <cstdint>
#include <string>

#include "../iwindow.hpp"

namespace sf {
    class Window;
}

namespace Scryver {

namespace Inputs {
    class UserInput;
}

namespace Engine {

class SFMLWindow : public IWindow
{
public:
    SFMLWindow();
    ~SFMLWindow() { destroy(); }
    bool initialize(uint16_t width = 800, uint16_t height = 600,
                    const std::string& title = "SFML Window");
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
    sf::Window*             m_window;
    Inputs::UserInput*      m_userInput;
};

}  // namespace Engine

}  // namespace Scryver

#endif  // SCRYVER_ENGINE_SFML_WINDOW_HPP
