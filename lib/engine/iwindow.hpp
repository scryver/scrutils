#ifndef SCRYVER_ENGINE_WINDOW_INTERFACE_HPP
#define SCRYVER_ENGINE_WINDOW_INTERFACE_HPP

namespace Scryver {

namespace Engine {

class IWindow
{
public:
    virtual bool initialize(uint16_t width = 800, uint16_t height = 600,
                            const std::string& title = "Abstract Window") = 0;
    virtual void destroy()                              = 0;

    virtual bool isOpen()                       const   = 0;
    virtual void pollEvents()                           = 0;

    virtual void clear()                                = 0;
    virtual void display()                              = 0;

    virtual void close()                                = 0;

    virtual bool isKeyPressed(uint16_t key)     const   = 0;
    virtual bool isKeyReleased(uint16_t key)    const   = 0;
    virtual bool isKeyDown(uint16_t key)        const   = 0;
    virtual bool isKeyUp(uint16_t key)          const   = 0;

};

}  // namespace Engine

}  // namespace Scryver

#endif  // SCRYVER_ENGINE_WINDOW_INTERFACE_HPP

// Window should be check if needed to be open
// Window should poll events and fill key mapper/mouse mapper
