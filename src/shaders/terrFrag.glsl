#version 330 core

in vec2 TexCoords;
in float visibility;
in vec3 surfaceNormal;
in vec3 toLightVector;


uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;
uniform vec3 fogColour;
uniform vec3 lightColour;

out vec4 color;
void main()
{
    //multitexturing calculations
    vec4 blendMapColour = texture(blendMap, TexCoords);
    float backTextureAmount = 1-(blendMapColour.r + blendMapColour.g + blendMapColour.b);
    vec2 tiledCoords = TexCoords * 10.0;
    vec4 backgroundTextureColour = texture(backgroundTexture, tiledCoords) * backTextureAmount;
    vec4 rTextureColour = texture(rTexture, tiledCoords) * blendMapColour.r;
    vec4 gTextureColour = texture(gTexture, tiledCoords) * blendMapColour.g;
    vec4 bTextureColour = texture(bTexture, tiledCoords) * blendMapColour.b;
    vec4 totalColour = backgroundTextureColour + rTextureColour + gTextureColour + bTextureColour;

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightVector);

    float nDotl = dot(unitNormal, unitLightVector) * 1.2;
    float brightness = max(nDotl, 0.2);
    vec3 diffuse = brightness * lightColour;

    color = vec4(diffuse, 1.0) * totalColour;
    color = mix(vec4(fogColour, 1.0), color, visibility);

}