#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;

out vec3 vertColour;

uniform mat4 model;

void main()
{
    vertColour = colour;
    gl_Position = model * vec4(position, 1.0);
}

