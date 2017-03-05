#ifndef SCRYVER_ENGINE_WINDOW_INTERFACE_HPP
#define SCRYVER_ENGINE_WINDOW_INTERFACE_HPP

#include <cstdint>
#include <string>

#include "Scryver/Math/Vector2D.hpp"

namespace Scryver {

namespace Engine {

class IWindow
{
public:
    IWindow() {}
    virtual ~IWindow() {}
    virtual bool initialize(uint16_t width = 800, uint16_t height = 600,
                            const std::string& title = "Abstract Window")   = 0;
    virtual bool initialize(const Math::Vector2D<uint16_t>& size,
                            const std::string& title = "Abstract Window")   = 0;
    virtual void destroy()                                                  = 0;

    Math::Vector2D<uint16_t> size() const { return m_size; }
    virtual void size(const Math::Vector2D<uint16_t>& size)                 = 0;
    uint16_t width() const { return m_size.x; }
    virtual void width(uint16_t w)                                          = 0;
    uint16_t height() const { return m_size.y; }
    virtual void height(uint16_t h)                                         = 0;

    virtual bool isOpen()                                           const   = 0;
    virtual void pollEvents()                                               = 0;

    virtual void clear()                                                    = 0;
    virtual void display()                                                  = 0;

    virtual void close()                                                    = 0;

    virtual bool isKeyPressed(uint16_t key)                         const   = 0;
    virtual bool isKeyReleased(uint16_t key)                        const   = 0;
    virtual bool isKeyDown(uint16_t key)                            const   = 0;
    virtual bool isKeyUp(uint16_t key)                              const   = 0;

    Math::Vector2Df mousePosition() const { return m_mousePosition; }
    virtual void mousePosition(const Math::Vector2Df& pos)                  = 0;

protected:
    Math::Vector2D<uint16_t>    m_size;
    Math::Vector2Df             m_mousePosition;
};

}  // namespace Engine

}  // namespace Scryver

#endif  // SCRYVER_ENGINE_WINDOW_INTERFACE_HPP

// Window should be check if needed to be open
// Window should poll events and fill key mapper/mouse mapper
