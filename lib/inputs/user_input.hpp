#ifndef SCRYVER_INPUTS_USERINPUT_HPP
#define SCRYVER_INPUTS_USERINPUT_HPP

#include <cstdint>

#include <unordered_map>

#include "Scryver/Math/Vector2D.hpp"

namespace Scryver {

namespace Inputs {

class UserInput
{
public:
    UserInput();
    ~UserInput();

    bool initialize(uint16_t expectedNrKeys = 32);
    void destroy();

    void update();

    void pressKey(uint16_t keyID);
    void releaseKey(uint16_t keyID);

    bool isKeyDown(uint16_t keyID) const;
    bool isKeyUp(uint16_t keyID) const;
    // Is key pressed this frame
    bool isKeyPressed(uint16_t keyID) const;
    bool isKeyReleased(uint16_t keyID) const;

    inline float getMouseX() const;
    inline float getMouseY() const;
    inline const Math::Vector2Df& getMouseCoords() const;
    inline void setMouseCoords(const Math::Vector2Df& coords);
    inline void setMouseCoords(float x, float y);

 private:
    Math::Vector2Df m_mouseCoords;
    std::unordered_map<uint16_t, bool> m_keyMap;
    std::unordered_map<uint16_t, bool> m_previousKeyMap;

    bool wasKeyDown(uint16_t keyID) const;
    bool wasKeyUp(uint16_t keyID) const;
};

#include "user_input.inl"

}  // namespace Inputs

}  // namespace Scryver

#endif  // SCRYVER_INPUTS_USERINPUT_HPP
