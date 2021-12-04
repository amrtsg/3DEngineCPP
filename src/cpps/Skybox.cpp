#include <Skybox.h>

const float SIZE = 1;
float skyboxVertices[] = {
	// positions          
	-SIZE,  SIZE, -SIZE,
	-SIZE, -SIZE, -SIZE,
	SIZE, -SIZE, -SIZE,
	 SIZE, -SIZE, -SIZE,
	 SIZE,  SIZE, -SIZE,
	-SIZE,  SIZE, -SIZE,

	-SIZE, -SIZE,  SIZE,
	-SIZE, -SIZE, -SIZE,
	-SIZE,  SIZE, -SIZE,
	-SIZE,  SIZE, -SIZE,
	-SIZE,  SIZE,  SIZE,
	-SIZE, -SIZE,  SIZE,

	 SIZE, -SIZE, -SIZE,
	 SIZE, -SIZE,  SIZE,
	 SIZE,  SIZE,  SIZE,
	 SIZE,  SIZE,  SIZE,
	 SIZE,  SIZE, -SIZE,
	 SIZE, -SIZE, -SIZE,

	-SIZE, -SIZE,  SIZE,
	-SIZE,  SIZE,  SIZE,
	 SIZE,  SIZE,  SIZE,
	 SIZE,  SIZE,  SIZE,
	 SIZE, -SIZE,  SIZE,
	-SIZE, -SIZE,  SIZE,

	-SIZE,  SIZE, -SIZE,
	 SIZE,  SIZE, -SIZE,
	 SIZE,  SIZE,  SIZE,
	 SIZE,  SIZE,  SIZE,
	-SIZE,  SIZE,  SIZE,
	-SIZE,  SIZE, -SIZE,

	-SIZE, -SIZE, -SIZE,
	-SIZE, -SIZE,  SIZE,
	 SIZE, -SIZE, -SIZE,
	 SIZE, -SIZE, -SIZE,
	-SIZE, -SIZE,  SIZE,
	 SIZE, -SIZE,  SIZE
};

void Skybox::stopDepthBuffer() {
	glDepthMask(GL_FALSE); //stop skybox from being drawn on the depth buffer
	glDepthRange(1, 1); //which will draw the skybox behind all other objects
	glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
}

void Skybox::setDefaultDepthBuffer() {
	glDepthFunc(GL_LESS); // set depth function back to default
	glDepthRange(0, 1); // set depth range back to default
	glDepthMask(GL_TRUE); //set depth mask back to default
}

void Skybox::setupSkybox() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);
	this->shader = new Shader("..\\..\\src\\shaders\\skyboxVert.glsl", "..\\..\\src\\shaders\\skyboxFrag.glsl");
	vector<string> faces = addFaces();
	cubemapTexture = Texture::loadCubeMap(faces);
}

void Skybox::draw() {
	stopDepthBuffer();
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	setDefaultDepthBuffer();
}

vector<string> Skybox::addFaces() {
	vector<string> faces;
	faces.push_back("..\\..\\res\\skybox\\right.jpg");
	faces.push_back("..\\..\\res\\skybox\\left.jpg");
	faces.push_back("..\\..\\res\\skybox\\top.jpg");
	faces.push_back("..\\..\\res\\skybox\\bottom.jpg");
	faces.push_back("..\\..\\res\\skybox\\front.jpg");
	faces.push_back("..\\..\\res\\skybox\\back.jpg");
	return faces;
}

Shader* Skybox::getShader() {
	return this->shader;
}

glm::mat4 Skybox::getViewMatrix(Camera camera) {
	glm::mat4 view = camera.GetViewMatrix();
	view = glm::rotate(glm::mat4(glm::mat3(camera.GetViewMatrix())), (GLfloat)glfwGetTime() * 0.05f, glm::vec3(0.0f, 1.0f, 0.0f));//remove translation & rotate skybox

	return view;
}