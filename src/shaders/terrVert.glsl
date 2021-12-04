#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform vec4 clipPlane;
uniform vec3 lightPosition;

out vec2 TexCoords;
out float visibility;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 vposition;

uniform float density;
uniform float gradient;

void main()
{
	vec4 worldPosition = model * vec4(position, 1.0f);
	vec4 positionRelativeToCam = view * worldPosition;
	gl_ClipDistance[0] = dot(worldPosition, clipPlane);
	gl_Position = projection * positionRelativeToCam;

	float distance = length(positionRelativeToCam.xyz);
    visibility = exp(-pow((distance*density), gradient));
    visibility = clamp(visibility, 0.0, 1.0);

	TexCoords = position.xz; //to tile textures, just multiply.
	vposition = position;
	surfaceNormal = (model * vec4(normal, 0.0)).xyz;
	toLightVector = lightPosition - worldPosition.xyz;
}