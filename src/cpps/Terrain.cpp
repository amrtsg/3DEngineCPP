#include "Terrain.h"
#include <stb_image.h>

GLint backgroundTexture;
GLint rTexture;
GLint gTexture;
GLint bTexture;
GLint blendMap;
Texture texture1(backgroundTexture);
Texture texture2(rTexture);
Texture texture3(gTexture);
Texture texture4(bTexture);
Texture texture5(blendMap);

//perlin noise variables
const int PERIOD = 64;
Perlin perlin(255, 255);

Terrain::Terrain(const char* imagePath, glm::vec3 position, float size, float heightStrength) {
	this->imagePath = imagePath;
	this->size = size;
	this->position = position;
	this->heightStrength = heightStrength;
	period = PERIOD;
	frequency = (float)1 / period;
	this->shader = new Shader("..\\..\\src\\shaders\\terrVert.glsl", "..\\..\\src\\shaders\\terrFrag.glsl");
	backgroundTexture = texture1.loadTexture("..\\..\\res\\grass.png");
	rTexture = texture2.loadTexture("..\\..\\res\\mud.png");
	gTexture = texture3.loadTexture("..\\..\\res\\flowers.png");
	bTexture = texture4.loadTexture("..\\..\\res\\snow.jpg");
	blendMap = texture5.loadTexture("..\\..\\res\\blendMap.png");
	terrModel = glm::scale(glm::mat4(1.0f), glm::vec3(this->size, 1.0f, this->size));
	terrModel = glm::translate(terrModel, this->position);
	heightMap = stbi_load(imagePath, &heightMapWidth, &heightMapHeight, &numOfChannels, 0);
	setupTerrain();
}

Terrain::Terrain(glm::vec3 position, float size, float heightStrength) {
	this->size = size;
	this->position = position;
	this->heightStrength = heightStrength;
	period = PERIOD;
	frequency = (float)1 / period;
	this->shader = new Shader("..\\..\\src\\shaders\\terrVert.glsl", "..\\..\\src\\shaders\\terrFrag.glsl");
	backgroundTexture = texture1.loadTexture("..\\..\\res\\grass.png");
	rTexture = texture2.loadTexture("..\\..\\res\\mud.png");
	gTexture = texture3.loadTexture("..\\..\\res\\flowers.png");
	bTexture = texture4.loadTexture("..\\..\\res\\snow.jpg");
	blendMap = texture5.loadTexture("..\\..\\res\\blendMap.png");
	terrModel = glm::scale(glm::mat4(1.0f), glm::vec3(this->size, 1.0f, this->size));
	terrModel = glm::translate(terrModel, this->position);
	setupProceduralTerrain();
}


void Terrain::setupProceduralTerrain() {
	createProceduralVertexData();
	createProceduralIndexData();

	//generate & bind vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//specify vertex buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//specify index buffer
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(short), &indices.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//specify normal buffer
	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terrain::setupTerrain() {
	createVertexData();
	createIndexData();
	checkHeightMapLoaded();

	//generate & bind vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//specify vertex buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//specify index buffer
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(short), &indices.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//specify normal buffer
	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terrain::draw() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, rTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gTexture);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, bTexture);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, blendMap);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}

void Terrain::createVertexData() {
	cout << "\033[31mHeight Map width: \033[0m" << heightMapWidth << "\033[31m Height Map height: \033[0m" << heightMapHeight << endl << endl;
	for (int row = 0; row < 255; row++) {
		for (int col = 0; col < 255; col++) {

			unsigned char* pixelOffset = heightMap + (row + heightMapHeight * col) * numOfChannels;
			unsigned char red = pixelOffset[0];

			float x = ((float)col / (float)(heightMapWidth - 1)) - 0.5f;
			float y = (float)red / heightStrength;
			float z = ((float)row / (float)(heightMapHeight - 1)) - 0.5f;

			vertices.push_back(glm::vec3(x, y, z));
			createNormalData(row, col);
		}
	}
	delete heightMap;
}

void Terrain::createProceduralVertexData() {
	for (int row = 0; row < 255; row++) {
		for (int col = 0; col < 255; col++) {
			glm::vec3 point(col, row, 0);
			
			noise = perlin.noise(col * frequency, row * frequency, 0);
			//noise = perlin.FBM(point, 0.8, 2, 4);
			noise = (noise + 1) * 0.5;
			int red = round(255 * noise);

			float x = ((float)col / (float)(perlin.width - 1)) - 0.5f;
			float y = (float)red / heightStrength;
			float z = ((float)row / (float)(perlin.height - 1)) - 0.5f;

			vertices.push_back(glm::vec3(x, y, z));
			createProceduralNormalData(row, col);
		}
	}
}

float Terrain::getProceduralHeight(int x, int z) {
	noise = perlin.noise(x * frequency, z * frequency, 0);
	noise = (noise + 1) * 0.5;
	int red = round(255 * noise);
	float y = (float)red / heightStrength;
	return y;
}

float Terrain::getHeight(int x, int z) {
	unsigned char* pixelOffset = heightMap + (x + heightMapHeight * z) * numOfChannels;
	unsigned char red = pixelOffset[0];
	float y = (float)red / heightStrength;
	return y;
}


void Terrain::createProceduralNormalData(float x, float z) {
	float heightL = getProceduralHeight(x-1, z);
	float heightR = getProceduralHeight(x+1, z);
	float heightD = getProceduralHeight(x, z-1);
	float heightU = getProceduralHeight(x, z+1);

	glm::vec3 normal(heightL - heightR, 2, heightD - heightU);
	glm::normalize(normal);
	normals.push_back(normal);
}

void Terrain::createNormalData(float x, float z) {
	float heightL = getHeight(x - 1, z);
	float heightR = getHeight(x + 1, z);
	float heightD = getHeight(x, z - 1);
	float heightU = getHeight(x, z + 1);

	glm::vec3 normal(heightL - heightR, 2, heightD - heightU);
	glm::normalize(normal);
	normals.push_back(normal);
}

void Terrain::createIndexData() {
	for (int row = 0; row < heightMapHeight - 1; row++) {
		for (int col = 0; col < heightMapWidth - 1; col++) {
			int TL = (int)(row * heightMapWidth + col);
			int TR = (int)(row * heightMapWidth + col + 1);
			int BL = (int)((row + 1) * heightMapWidth + col);
			int BR = (int)((row + 1) * heightMapWidth + col + 1);
			indices.push_back(TL);
			indices.push_back(BL);
			indices.push_back(TR);
			indices.push_back(TR);
			indices.push_back(BL);
			indices.push_back(BR);
		}
	}
}

void Terrain::createProceduralIndexData() {
	for (int row = 0; row < perlin.height - 1; row++) {
		for (int col = 0; col < perlin.width - 1; col++) {
			int TL = (int)(row * perlin.width + col);
			int TR = (int)(row * perlin.width + col + 1);
			int BL = (int)((row + 1) * perlin.width + col);
			int BR = (int)((row + 1) * perlin.width + col + 1);
			indices.push_back(TL);
			indices.push_back(BL);
			indices.push_back(TR);
			indices.push_back(TR);
			indices.push_back(BL);
			indices.push_back(BR);
		}
	}
}

void Terrain::checkHeightMapLoaded() {
	if (heightMapWidth == 0 || heightMapHeight == 0) {
		cout << "\033[31mHeight Map failed to load\033[0m\n";
		return;
	}
	else if (heightMapWidth > 255 || heightMapHeight > 255) {
		cout << "\033[31mHEIGHT MAP SIZE GREATER THAN 255x255! RESIZE DOWN!!\033[0m" << endl;
	}
	else {
		cout << "\033[32mHeight Map " << imagePath << " loaded successfully\033[0m\n\n""";
	}
}

glm::mat4 Terrain::getModelMatrix() {
	return  terrModel;
}

Shader* Terrain::getShader() {
	return shader;
}