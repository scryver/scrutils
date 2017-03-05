#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 camera;
uniform mat4 world;

out vec3 vertColour;

void main()
{
    vertColour = position;
    gl_Position = camera * world * vec4(position, 1.0);
}

