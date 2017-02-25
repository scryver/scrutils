#version 330 core

layout (location = 0) in vec3 position;

out vec3 texCoords;

uniform mat4 camera;
// uniform mat4 view;

void main()
{
    // gl_Position =   projection * view * vec4(position, 1.0);
    gl_Position = camera * vec4(position, 1.0);
    texCoords = gl_Position.xyz;
}
