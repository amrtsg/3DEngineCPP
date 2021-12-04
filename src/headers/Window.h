#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>
#include <Camera.h>

using namespace std;

const static int WIN_WIDTH = 800;
const static int WIN_HEIGHT = 600;

class Window {

public:
	Window();
	void specifyHints();
	void startGLFW();
	void startGLEW();
	void setupWindow();

public:
	int WIDTH;
	int HEIGHT;
	GLFWwindow* window;
};
