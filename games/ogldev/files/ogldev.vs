#version 330 core

layout(location = 0) in vec3 position;
// layout(location = 1) in vec3 colour;

// out vec3 vertColour;

uniform float gScale;
uniform mat4 world;

void main()
{
    // vertColour = colour;
    // gl_Position = model * vec4(position, 1.0);
    gl_Position = world * vec4(gScale * position.x, gScale * position.y, position.z, 1.0);
    // gl_Position = vec4(position, 1.0);
}

