#version 330 core

in vec3 vertColour;
in vec2 vertCoord;

out vec4 colour;

uniform sampler2D texSampler;

void main()
{
    vec4 t = texture(texSampler, vertCoord);
    colour = t;
}
