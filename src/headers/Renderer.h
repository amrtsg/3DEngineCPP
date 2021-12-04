/*
Renderer.h
*/

#pragma once

#include <Terrain.h>
#include <Model.h>
#include <WaterTile.h>
#include <Skybox.h>
#include <Camera.h>
#include <Light.h>

using namespace std;

class Renderer
{
public:
	//render all objects to scene
	void renderScene(Light light, vector<WaterTile> tiles, Skybox skybox, vector<Model> entities, vector<Terrain> terrains, glm::mat4 view, glm::mat4 projection, Camera camera, glm::vec4 clipPlane);
	//render objects excluding water to scene
	void renderSceneNoWater(Light light, Skybox skybox, vector<Model> entities, vector<Terrain> terrains, glm::mat4 view, glm::mat4 projection, Camera camera, glm::vec4 clipPlane);
};

