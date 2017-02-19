#version 330 core

in vec3 vertColour;

out vec3 colour;

void main()
{
    colour = clamp(vertColour + vec3(0.3, 0.5, 0.6), 0.0, 1.0);
}
