#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <Texture.h>
#include <Renderer.h>
#include <random>

using namespace std;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);

Window win;
GLfloat lastX = win.WIDTH / 2.0;
GLfloat lastY = win.HEIGHT / 2.0;
Camera camera(glm::vec3(-45.0f, 5.0f, 25.0f));
bool firstMouse = true;
bool keys[1024];
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
vector<Model> models;
vector<Terrain> terrains;
vector<WaterTile> waters;

void createCity(vector<Model>& models) {
	random_device rd;
	default_random_engine generator(rd()); // rd() provides a random seed
	uniform_real_distribution<float> x(-130, -60);
	uniform_real_distribution<float> z(60, 140);
	uniform_real_distribution<float> angle(0, 180);

	Model house("..\\..\\res\\tree\\cottage\\house.obj", glm::vec3(-125, 2.0, 80), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 1, 0), -120.0f);
	models.push_back(house);
	for (int i = 0; i < 5; i++) {
		float randX = x(generator);
		float randZ = z(generator);
		Model deadtree("..\\..\\res\\tree\\deadtree\\deadtree.obj", glm::vec3(randX, 2.0, randZ), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 0), 0.0f);
		models.push_back(deadtree);
	}
	for (int i = 0; i < 3; i++) {
		float randX = x(generator);
		float randZ = z(generator);
		Model rock("..\\..\\res\\tree\\rock\\rock.obj", glm::vec3(randX, 3.0, randZ), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 0), 0.0f);
		models.push_back(rock);
	}
	for (int i = 0; i < 15; i++) {
		float randX = x(generator);
		float randZ = z(generator);
		Model grass("..\\..\\res\\tree\\grass\\grass.obj", glm::vec3(randX, 2.0, randZ), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0, 0, 0), 0.0f);
		models.push_back(grass);
	}
	for (int i = 0; i < 5; i++) {
		float randX = x(generator);
		float randZ = z(generator);
		float randAngle = angle(generator);
		Model crate("..\\..\\res\\tree\\crate\\box.obj", glm::vec3(randX, 2.0, randZ), glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0, 0, 0), randAngle);
		models.push_back(crate);
	}
	//front border
	Model wall1("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-68.5, 2.0, 59), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 0, 0), 0.0f);
	Model wall4("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-83.4, 2.0, 59), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 0, 0), 0.0f);
	Model wall2("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-125.1, 2.0, 59), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 0, 0), 0.0f);
	Model wall3("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-140, 2.0, 59), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 0, 0), 0.0f);
	//left border
	Model wall5("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-57.5, 2.0, 69), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 1, 0), 90.0f);
	Model wall6("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-57.5, 2.0, 82.5), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 1, 0), 90.0f);
	Model wall7("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-57.5, 2.0, 96), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 1, 0), 90.0f);
	Model wall8("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-57.5, 2.0, 109.5), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 1, 0), 90.0f);
	Model wall9("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-57.5, 2.0, 123.0), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 1, 0), 90.0f);
	Model wall10("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-57.5, 2.0, 137.5), glm::vec3(1.1f, 0.75f, 1.1f), glm::vec3(0, 1, 0), 90.0f);
	//back border
	Model wall11("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-68.5, 2.0, 142), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 0, 0), 0.0f);
	Model wall12("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-83.4, 2.0, 142), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 0, 0), 0.0f);
	Model wall13("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-125.1, 2.0, 142), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 0, 0), 0.0f);
	Model wall14("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-140, 2.0, 142), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 0, 0), 0.0f);
	Model wall21("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-98.3, 2.0, 142), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 0, 0), 0.0f);
	Model wall22("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-111.2, 2.0, 142), glm::vec3(0.9f, 0.75f, 1.0f), glm::vec3(0, 0, 0), 0.0f);
	//right border
	Model wall15("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-143.5, 2.0, 69), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 1, 0), 90.0f);
	Model wall16("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-143.5, 2.0, 82.5), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 1, 0), 90.0f);
	Model wall17("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-143.5, 2.0, 96), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 1, 0), 90.0f);
	Model wall18("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-143.5, 2.0, 109.5), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 1, 0), 90.0f);
	Model wall19("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-143.5, 2.0, 123.0), glm::vec3(1.1f, 0.75f, 1.0f), glm::vec3(0, 1, 0), 90.0f);
	Model wall20("..\\..\\res\\tree\\wall\\wall.obj", glm::vec3(-143.5, 2.0, 137.5), glm::vec3(1.1f, 0.75f, 1.1f), glm::vec3(0, 1, 0), 90.0f);
	models.push_back(wall1);
	models.push_back(wall2);
	models.push_back(wall3);
	models.push_back(wall4);
	models.push_back(wall5);
	models.push_back(wall6);
	models.push_back(wall7);
	models.push_back(wall8);
	models.push_back(wall9);
	models.push_back(wall10);
	models.push_back(wall11);
	models.push_back(wall12);
	models.push_back(wall13);
	models.push_back(wall14);
	models.push_back(wall15);
	models.push_back(wall16);
	models.push_back(wall17);
	models.push_back(wall18);
	models.push_back(wall19);
	models.push_back(wall20);
	models.push_back(wall21);
	models.push_back(wall22);
	Model bridge("..\\..\\res\\tree\\bridge\\bridge.obj", glm::vec3(-102.0, 1.7, 25.0), glm::vec3(3.0f, 3.0f, 9.0f), glm::vec3(0, 1, 0), 90.0f);
	models.push_back(bridge);
	Model boat("..\\..\\res\\tree\\boat\\boat.obj", glm::vec3(-60, 3.0, 33.0), glm::vec3(1.5f, 1.5f, 1.5f), glm::vec3(0, 1, 0), 45.0f);
	models.push_back(boat);
	Model bigRock("..\\..\\res\\tree\\rock\\rock.obj", glm::vec3(-8.0, 3.0, 79.0), glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0, 0, 0), 0.0f);
	models.push_back(bigRock);
	for (int i = 0; i < 8; i++) {
		float randX = x(generator);
		float randZ = z(generator);
		Model tree("..\\..\\res\\tree\\firTree\\tree.obj", glm::vec3(randX, 2.0, randZ), glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0, 0, 0), 0.0f);
		models.push_back(tree);
	}
}

int main() {

	//setup and create window
	Window win;
	win.setupWindow();
	//glfw input callbacks
	glfwSetKeyCallback(win.window, KeyCallback);
	glfwSetCursorPosCallback(win.window, MouseCallback);

	//load objects
	//Terrain terrain(glm::vec3(0, -11.5, 0), 400.0f, 10.0);
	Terrain terrain2("..\\..\\res\\heightmaps\\terrHeightMap7.png", glm::vec3(-1, 0, 0), 100.0f, 30.0);
	Terrain terrain4("..\\..\\res\\heightmaps\\terrHeightMap3.png", glm::vec3(0, 0, 0), 100.0f, 5.0); //mountain
	Terrain terrain5("..\\..\\res\\heightmaps\\terrHeightMap3.png", glm::vec3(0, 0, 1), 100.0f, 40.0);
	Terrain terrain6("..\\..\\res\\heightmaps\\terrHeightMap4.jpg", glm::vec3(-1, 0, 1), 100.0f, 20.0);
	//terrains.push_back(terrain);
	terrains.push_back(terrain2);
	terrains.push_back(terrain4);
	terrains.push_back(terrain5);
	terrains.push_back(terrain6);


	WaterFrameBuffer fbo;
	WaterTile tile(glm::vec3(-0.5, 1.5, 0.5), glm::vec2(100, 100), fbo);
	tile.setupWater();
	waters.push_back(tile);
	Light light(glm::vec3(10000.0, 10000.0, 10000.0), glm::vec3(1, 1, 1));
	Skybox skybox;
	Renderer renderer;

	//setup objects
	skybox.setupSkybox();
	createCity(models);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Main gameloop
	while (!glfwWindowShouldClose(win.window)) {
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		cout << camera.position.x << " " << camera.position.y << " " << camera.position.z << endl;
		camera.moveCamera(keys, deltaTime);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//enable clip distance
		glEnable(GL_CLIP_DISTANCE0);


		//create VP Matrices
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.GetFOV(), (float)win.WIDTH / (float)win.HEIGHT, 0.1f, 1000.0f);

		//render to reflection texture
		fbo.bindReflectionFrameBuffer();
		float distance = 2 * (camera.position.y - tile.getHeight());
		camera.position.y -= distance; //move camera above the water
		camera.invertPitch();
		renderer.renderSceneNoWater(light, skybox, models, terrains, view, projection, camera, glm::vec4(0, 1, 0, -tile.getHeight()));
		camera.position.y += distance; //move camera back to original position
		camera.invertPitch();

		//render to refraction texture
		fbo.bindRefractionFrameBuffer();
		renderer.renderSceneNoWater(light, skybox, models, terrains, view, projection, camera, glm::vec4(0, -1, 0, tile.getHeight() + 1));

		//switch to original frame buffer
		fbo.unbindCurrentFrameBuffer();

		//render to screen
		glDisable(GL_CLIP_DISTANCE0);
		//^ this line doesn't work on some graphics cards so we set the height to a very high number to be safe.
		renderer.renderScene(light, waters, skybox, models, terrains, view, projection, camera, glm::vec4(0, 1, 0, 99999999));

		glfwSwapBuffers(win.window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

//GLFW Handle key pressed
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			keys[key] = false;
		}
	}
}

//GLFW Handle mouse movements
void MouseCallback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  //y-coordinates go from bottom to left SO REVERSE IT

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}