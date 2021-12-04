#include <WaterTile.h>

//declare texture locations
GLuint dudvID;
GLuint normalMapID;
//declare a texture with dudv location
Texture dudvTex(dudvID);
Texture normalMapTex(normalMapID);
//declare wave variables
GLfloat WAVE_SPEED = 0.0002f;
GLfloat moveFactor = 0.0f;

//these vertices are only the x and z, the y is set to 0 in the vertex shader.
GLfloat vertices[] = { 
	-1, -1,
	-1,  1,
	 1, -1,
	 1, -1,
	-1,  1,
	 1,  1 
};

//Watertile constructor
WaterTile::WaterTile(glm::vec3 position, glm::vec2 size, WaterFrameBuffer fbos) {
	this->position = position;
	this->size = size;
	this->shader = new Shader("..\\..\\src\\water\\waterVert.glsl", "..\\..\\src\\water\\waterFrag.glsl");
	this->fbos = fbos;
	dudvID = dudvTex.loadTexture("..\\..\\res\\DUDV.png");
	normalMapID = normalMapTex.loadTexture("..\\..\\res\\normalMap.png");
}

//method to load the moveFactor variable to shader
void WaterTile::loadMoveFactor() {
	GLint moveLoc = glGetUniformLocation(shader->Program, "moveFactor");
	glUniform1f(moveLoc, moveFactor);
}

void WaterTile::loadCameraPos(Camera camera) {
	GLint cameraLoc = glGetUniformLocation(shader->Program, "cameraPosition");
	glUniform3f(cameraLoc, camera.position.x, camera.position.y, camera.position.z);
}

//render water tile
void WaterTile::render() {
	//setupWater();
	glBindVertexArray(vao);
	//add to move factor
	moveFactor += WAVE_SPEED;
	//reset move factor once it hits 1
	if (moveFactor >= 1.0f) {
		moveFactor = 0.0f;
	}
	loadMoveFactor();
	//bind reflection/refraction/dudv textures to water
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fbos.getReflectionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, fbos.getRefractionTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, dudvID);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, fbos.getRefractionDepthTexture());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, normalMapID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//draw water tile
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//create necessary vaos, vbos
void WaterTile::setupWater() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//specify indices for vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

}

//unbind vao
void WaterTile::unbind() {
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

//create and return model matrix
glm::mat4 WaterTile::getModelMatrix() {
	glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(this->size.x, 1.0f, this->size.y));
	model = glm::translate(model, this->position);
	return model;
}

//return height
float WaterTile::getHeight() {
	return position.y;
}

//return pointer to shader
Shader* WaterTile::getShader() {
	return shader;
}