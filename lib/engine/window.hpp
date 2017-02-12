#ifndef SCRYVER_ENGINE_WINDOW_HPP
#define SCRYVER_ENGINE_WINDOW_HPP

namespace Scryver {

namespace Engine {

class Window
{
public:
    bool Initialize() = 0;
    void Destroy() = 0;

    bool IsOpen() const = 0;
    bool PollEvents() = 0;
};

}  // namespace Engine

}  // namespace Scryver

#endif  // SCRYVER_ENGINE_WINDOW_HPP

// Window should be check if needed to be open
// Window should poll events and fill key mapper/mouse mapper
