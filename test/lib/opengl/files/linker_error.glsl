#version 330 core

in vec2 vertColour;

out vec3 colour;

void main()
{
    colour = vec3(vertColour, 0.3);
}
