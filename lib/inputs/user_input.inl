float UserInput::getMouseX() const
{
    return m_mouseCoords.x;
}

float UserInput::getMouseY() const
{
    return m_mouseCoords.y;
}

const Math::Vector2Df& UserInput::getMouseCoords() const
{
    return m_mouseCoords;
}

void UserInput::setMouseCoords(const Math::Vector2Df& coords)
{
    m_mouseCoords = coords;
}

void UserInput::setMouseCoords(float x, float y)
{
    m_mouseCoords.x = x;
    m_mouseCoords.y = y;
}
