#include <Renderer.h>

//fog variables
const glm::vec3 SKY_COLOR(0.878, 0.945, 1);//0.5444, 0.62, 0.69 darker fog
const float DENSITY = 0.003; //0.01
const float GRADIENT = 1.5;
const float LOWER_LIMIT = 0.0;
const float UPPER_LIMIT = 0.2;

//Render all objects in scene
void Renderer::renderScene(Light light, vector<WaterTile> tiles, Skybox skybox, vector<Model> entities, vector<Terrain> terrains, glm::mat4 view, glm::mat4 projection, Camera camera, glm::vec4 clipPlane) {
	//Draw Water_________________________________________________________________
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i].getShader()->use();
		tiles[i].getShader()->setUniforms(tiles[i].getModelMatrix(), view, projection);
		tiles[i].getShader()->loadWaterTextures();
		tiles[i].getShader()->loadLightVariables(light.getPosition(), light.getColour());
		tiles[i].loadCameraPos(camera);
		tiles[i].render();
	}

	//Draw Terrain_______________________________________________________________
	for (int i = 0; i < terrains.size(); i++) {
		terrains[i].getShader()->use();
		terrains[i].getShader()->setUniforms(terrains[i].getModelMatrix(), view, projection);
		terrains[i].getShader()->loadFogVariables(SKY_COLOR, DENSITY, GRADIENT);
		terrains[i].getShader()->loadClipPlane(clipPlane);
		terrains[i].getShader()->loadLightVariables(light.getPosition(), light.getColour());
		terrains[i].getShader()->loadTerrainTextures();
		terrains[i].draw();
	}

	//Draw skybox _______________________________________________________________
	skybox.getShader()->use();
	skybox.getShader()->setUniforms(skybox.getViewMatrix(camera), projection);
	skybox.getShader()->loadSkyboxVariables(SKY_COLOR, UPPER_LIMIT, LOWER_LIMIT);
	skybox.draw();

	for (int i = 0; i < entities.size(); i++) {
		//DRAW .OBJ__________________________________________________________________
		entities[i].getShader()->use();
		entities[i].getShader()->setUniforms(entities[i].getModelMatrix(), view, projection);
		entities[i].getShader()->loadFogVariables(SKY_COLOR, DENSITY, GRADIENT);
		entities[i].getShader()->loadClipPlane(clipPlane);
		entities[i].draw(entities[i].getShader());
	}

}

//Render all objects in scene without water
void Renderer::renderSceneNoWater(Light light, Skybox skybox, vector<Model> entities, vector<Terrain> terrains, glm::mat4 view, glm::mat4 projection, Camera camera, glm::vec4 clipPlane) {

	//Draw Terrain_______________________________________________________________
	for (int i = 0; i < terrains.size(); i++) {
		terrains[i].getShader()->use();
		terrains[i].getShader()->setUniforms(terrains[i].getModelMatrix(), camera.GetViewMatrix(), projection);
		terrains[i].getShader()->loadFogVariables(SKY_COLOR, DENSITY, GRADIENT);
		terrains[i].getShader()->loadClipPlane(clipPlane);
		terrains[i].getShader()->loadLightVariables(light.getPosition(), light.getColour());
		terrains[i].getShader()->loadTerrainTextures();
		terrains[i].draw();
	}

	//Draw skybox _______________________________________________________________
	skybox.getShader()->use();
	skybox.getShader()->setUniforms(skybox.getViewMatrix(camera), projection);
	skybox.getShader()->loadSkyboxVariables(SKY_COLOR, UPPER_LIMIT, LOWER_LIMIT);
	skybox.draw();


	for (int i = 0; i < entities.size(); i++) {
		//DRAW .OBJ__________________________________________________________________
		entities[i].getShader()->use();
		entities[i].getShader()->setUniforms(entities[i].getModelMatrix(), camera.GetViewMatrix(), projection);
		entities[i].getShader()->loadFogVariables(SKY_COLOR, DENSITY, GRADIENT);
		entities[i].getShader()->loadClipPlane(clipPlane);
		entities[i].draw(entities[i].getShader());
	}

}