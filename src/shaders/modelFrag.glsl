#version 330 core

in vec2 TexCoords;
in float visibility;

out vec4 color;

uniform sampler2D modelTexture;
uniform vec3 fogColour;

uniform vec3 lightColour;

void main( )
{
    color = vec4( texture( modelTexture, TexCoords ));
    //color = vec4(1.0, 0.0, 0.0, 1.0);
    color = mix(vec4(fogColour, 1.0), color, visibility);
}