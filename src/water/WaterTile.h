/*
WaterTile.h
*/

#pragma once

#include <GL/glew.h>
#include <vector>
#include <gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <Model.h>
#include <WaterFrameBuffer.h>
#include <Texture.h>

using namespace std;

class WaterTile
{
public:
	//constructor
	WaterTile(glm::vec3 position, glm::vec2 size, WaterFrameBuffer fbos);
	//getters
	float getHeight();
	float getX();
	float getZ();
	Shader* getShader();
	glm::mat4 getModelMatrix();
	//draw water to scene
	void render();
	void unbind();
	//create necessary vaos, vbos
	void setupWater();
	//load moveFactor variable to shader
	void loadMoveFactor();
	//load camera position values to shader
	void loadCameraPos(Camera camera);

private:
	float x, z;
	Shader* shader;
	GLuint vao, vbo;
	glm::vec2 size;
	glm::vec3 position;
	WaterFrameBuffer fbos;
};

