#include "user_input.hpp"

using Scryver::Inputs::UserInput;

UserInput::UserInput()
    : m_mouseCoords(0.0f, 0.0f)
{
    // Empty
}

UserInput::~UserInput()
{
    destroy();
}

bool UserInput::initialize(uint16_t expectedNrKeys)
{
    m_keyMap.reserve(expectedNrKeys);
    m_previousKeyMap.reserve(expectedNrKeys);
    return true;
}

void UserInput::destroy()
{
    m_keyMap.clear();
    m_previousKeyMap.clear();
}

void UserInput::update()
{
    for (auto& it : m_keyMap) {
        m_previousKeyMap[it.first] = it.second;
    }
}

void UserInput::pressKey(uint16_t keyID)
{
    m_keyMap[keyID] = true;
}

void UserInput::releaseKey(uint16_t keyID)
{
    m_keyMap[keyID] = false;
}

bool UserInput::isKeyDown(uint16_t keyID) const
{
    auto it = m_keyMap.find(keyID);

    if (it != m_keyMap.end()) {
        return it->second;
    }
    return false;
}

bool UserInput::isKeyUp(uint16_t keyID) const
{
    return !isKeyDown(keyID);
}

bool UserInput::isKeyPressed(uint16_t keyID) const
{
    if (isKeyDown(keyID) && !wasKeyDown(keyID)) {
        return true;
    }
    return false;
}

bool UserInput::isKeyReleased(uint16_t keyID) const
{
    return !isKeyPressed(keyID);
}

bool UserInput::wasKeyDown(uint16_t keyID) const
{
    auto it = m_previousKeyMap.find(keyID);

    if (it != m_previousKeyMap.end()) {
        return it->second;
    }
    return false;
}

bool UserInput::wasKeyUp(uint16_t keyID) const
{
    return !wasKeyDown(keyID);
}

