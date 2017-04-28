#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 world;
uniform mat4 camera;

out vec3 vertColour;
out vec2 vertCoord;

void main()
{
    vertColour = position;
    vertCoord = texCoord;
    gl_Position = camera * world * vec4(position, 1.0);
}

