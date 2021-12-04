#pragma once

#include <vector>
#include <iostream>
#include "GL/glew.h"
#include <Mesh.h>
#include <Texture.h>
#include <Camera.h>

using namespace std;

class Skybox
{
public:
	void setupSkybox();
	vector<string> addFaces();
	void stopDepthBuffer();
	void draw();
	void setDefaultDepthBuffer();
	Shader* getShader();
	glm::mat4 getViewMatrix(Camera camera);
	
public:
	GLuint vao;
	GLuint vbo;
	Shader* shader;
	unsigned int cubemapTexture;

};

