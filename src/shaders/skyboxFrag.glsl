#version 330 core
out vec4 color;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform vec3 fogColour;

uniform float lowerLimit;
uniform float upperLimit;

void main()
{    
    vec4 finalColour = texture(skybox, TexCoords);

    float factor = (TexCoords.y - lowerLimit) / (upperLimit - lowerLimit);
    factor = clamp(factor, 0.0, 1.0);
    color = mix(vec4(fogColour, 1.0), finalColour, factor);
}