#version 330 core

in vec3 vertColour;
in vec2 vertCoord;

out vec4 colour;

uniform sampler2D texSampler;
uniform sampler2D normSampler;

void main()
{
    vec4 t = texture(texSampler, vertCoord);
    vec4 s = texture(normSampler, vertCoord);
    // colour = clamp(t + s, 0.0, 1.0);
    colour = mix(s, t, 0.5);
}
