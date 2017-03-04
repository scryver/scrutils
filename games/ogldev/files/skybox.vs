#version 330 core

layout (location = 0) in vec3 position;

out vec3 texCoords;

uniform mat4 camera;
// uniform mat4 view;

void main()
{
    mat4 cameraPos;
    cameraPos[0].x = 1;
    cameraPos[1].y = 1;
    cameraPos[2].z = 1;
    cameraPos[3].w = 1;
    cameraPos[0].w = camera[0].w;
    cameraPos[1].w = camera[1].w;
    cameraPos[2].w = camera[2].w;
    // gl_Position =   projection * view * vec4(position, 1.0);
    gl_Position = cameraPos * vec4(position, 1.0);
    texCoords = position;
}
