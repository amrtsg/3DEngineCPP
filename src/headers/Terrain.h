#pragma once
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include "Model.h"
#include "Texture.h"
#include <Perlin.h>

class Terrain
{
private:
	//model properties
	vector<glm::vec3> vertices;
	vector<short> indices;
	vector<glm::vec3> normals;
	//height map variables
	int heightMapWidth;
	int heightMapHeight;
	int numOfChannels;
	const char* imagePath;
	//shader pointer
	Shader* shader;
	//creates vertices from height map
	void createVertexData();
	//creates vertices procedurally
	void createProceduralVertexData();
	//creates indices from height map
	void createIndexData();
	//creates indices procedurally
	void createProceduralIndexData();
	//creates normals and pushes them to normal vector
	void createNormalData(float x, float z);
	//creates normals and pushes them to normal vector
	void createProceduralNormalData(float x, float z);
	//error checking for heightmap
	void checkHeightMapLoaded();
	//terrain variables
	glm::vec3 position;
	float size;
	glm::mat4 terrModel;
	float heightStrength;
	//height map var used to get rgb colors (MAX SIZE 255x255!)
	unsigned char* heightMap;

	//PERLIN VARIABLES
	float noise;
	int period;
	float frequency;

public:
	//constructor using heightmap image
	Terrain(const char* imagePath, glm::vec3 position, float size, float heightStrength);
	//constructor using procedural generation
	Terrain(glm::vec3 position, float size, float heightStrength);
	//sets up vaos, vbos, should be called before loop
	void setupTerrain();
	//sets up vaos, vbos, should be called before loop (procedural)
	void setupProceduralTerrain();
	//gets the height at certain point in heightmap
	float getHeight(int x, int z);
	//gets the height at certain point in noise
	float getProceduralHeight(int x, int z);
	//draws terrain
	void draw();
	//getters
	Shader* getShader();
	glm::mat4 getModelMatrix();
	//opengl objects
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	GLuint nbo;
};
