#include <iostream>
#include <GL\glew.h>
#include "Display.h"
#include "Loader.h"
#include "EntityRenderer.h"
#include "MasterRenderer.h"
#include "StaticShader.h"
#include <glm\vec3.hpp>
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Camera.h"
#include "Light.h"
#include "TerrainShader.h"
#include "TerrainRenderer.h"
#include "Terrain.h"
#include "TerrainTexture.h"
#include "TerrainTexturePack.h"
#include "Player.h"
#include "GUIRenderer.h"
#include "GUITexture.h"
#include <list>
#include <vector>
#include "WaterShader.h"
#include "WaterTile.h"
#include "WaterRenderer.h"
#include "WaterFrameBuffer.h"

#define WIDTH 800
#define HEIGHT 600

int main(int arg, char** argv) {

	Display display(WIDTH, HEIGHT, "3D OpenGL");

	Loader loader;

	//------- texture pack
	TerrainTexture backgroundTexture(loader.LoadTexture("./res/grass.png"));
	TerrainTexture rTexture(loader.LoadTexture("./res/dirt.png"));
	TerrainTexture gTexture(loader.LoadTexture("./res/dirt2.png"));
	TerrainTexture bTexture(loader.LoadTexture("./res/stones.png"));
	TerrainTexture blendMap(loader.LoadTexture("./res/blendMap.png"));

	TerrainTexturePack texturePack(backgroundTexture, rTexture, gTexture, bTexture);
	//---------

	RawModel model = loader.LoadToVAO("./res/choocCandle.obj");
	ModelTexture texture(loader.LoadTexture("./res/tex.png"));
	texture.Shininess() = 999999;
	texture.Reflectivity() = 0;

	RawModel tree01 = loader.LoadToVAO("./res/tree01.obj");
	RawModel tree02 = loader.LoadToVAO("./res/tree02.obj");
	RawModel tree03 = loader.LoadToVAO("./res/tree03.obj");
	ModelTexture colorPalet(loader.LoadTexture("./res/colorPalet.png"));
	colorPalet.Shininess() = 999999;
	colorPalet.Reflectivity() = 0;
	TexturedModel texturedModel(model, texture);
	TexturedModel texturedTree01Model(tree01, colorPalet);
	TexturedModel texturedTree02Model(tree02, colorPalet);
	TexturedModel texturedTree03Model(tree03, colorPalet);

	std::vector<Terrain> terrains;
	Terrain terrain(0, 0, loader, texturePack, blendMap);
	terrains.push_back(terrain);
	//Terrain terrain2(-1, 0, loader, texturePack, blendMap);

	std::vector<Entity> entities;
	Player player(texturedModel, 0, glm::vec3(60, 0, 45), glm::vec3(0, 45, 0), glm::vec3(0.4, 0.4, 0.4));
	for (size_t i = 0; i < 100; i++) {
		int randTree = rand() % 3;
		glm::vec3 pos(rand() % 350 + 25, 0, rand() % 350 + 25);
		pos.y = terrain.GetHeight(pos.x, pos.z);
		switch (randTree) {
		case 0:
			entities.push_back(Entity(texturedTree01Model, 0, pos, glm::vec3(0, 45, 0), glm::vec3(4, 4, 4)));
			break;
		case 1:
			entities.push_back(Entity(texturedTree02Model, 0, pos, glm::vec3(0, 45, 0), glm::vec3(3, 3, 3)));
			break;
		case 2:
			entities.push_back(Entity(texturedTree03Model, 0, pos, glm::vec3(0, 45, 0), glm::vec3(3, 3, 3)));
			break;
		}
	}

	Light light(glm::vec3(60, 10, 45), glm::vec3(1, 1, 1), glm::vec3(1, 0.01f, 0.002f));

	Camera camera(glm::vec3(8, 2, 0), 70.f, (float)WIDTH / (float)HEIGHT, 0.01f, 400.0f, player);
	//Renderer renderer(shader);
	MasterRenderer masterRenderer(loader);

	GUIRenderer guiRenderer(loader);
	
	WaterShader wShader;
	wShader.BindAttributes();
	WaterRenderer waterRenderer(loader, wShader);
	std::vector<WaterTile> waterTiles;
	waterTiles.push_back(WaterTile(60, 45, 0));
	waterTiles.push_back(WaterTile(0, 0, 0));


	WaterFrameBuffer waterFrameBuffer;
	std::list<GUITexture> guis;
	waterFrameBuffer.BindReflectionFrameBuffer();
	GUITexture gui(waterFrameBuffer.GetReflectionTexture(), glm::vec2(0.5f, 0.5f), glm::vec2(0.25f, 0.25f));
	std::cout << waterFrameBuffer.GetReflectionTexture() << " main reflection texture.."<< std::endl;
	guis.push_back(gui);
	waterFrameBuffer.UnbindCurrentFrameBuffer();

	float counter = 0.0f;
	while (!display.IsClosed()) {
		display.Clear(0.2f, 0.2f, 0.2f, 1.0f);
		camera.Move(terrain);
		player.Move(terrain);
		glm::vec3 lPos = player.GetPosition();
		lPos.y += 5.0f;
		light.SetPosition(lPos);

		masterRenderer.RenderScene(entities, terrains, light, camera, player);

		waterFrameBuffer.BindReflectionFrameBuffer();
		masterRenderer.RenderScene(entities, terrains, light, camera, player);
		waterFrameBuffer.UnbindCurrentFrameBuffer();
		//waterRenderer.Render(waterTiles, camera);
		guiRenderer.Render(guis);


		display.Update();

		counter += 0.001f;
	}
	return 0;
}