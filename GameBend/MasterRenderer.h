#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include <list>
#include <map>
#include <vector>
#include "StaticShader.h"
#include "Entity.h"
#include "TexturedModel.h"
#include "Light.h"
#include "Camera.h"
#include "ModelRenderData.h"
#include "EntityRenderer.h"
#include "TerrainShader.h"
#include "TerrainRenderer.h"
#include "Terrain.h"
#include "SkyboxRenderer.h"
#include "Loader.h"

class MasterRenderer{
public:
	MasterRenderer(Loader& loader);
	~MasterRenderer();
	void RenderScene(std::vector<Entity> entities, std::vector<Terrain> terrains, Light lightSource, Camera camera, Entity& player);
	void Render(Light sun, Camera camera, Entity& player);
	void ProcessEntity(Entity& entity);
	void ProcessTerrain(Terrain& entity);

	static void EnableCulling();
	static void DisableCulling();
private:
	std::list<ModelRenderData> m_entities;
	std::list<Entity> m_listEntities;
	std::list<Terrain> m_terrains;

	SkyboxRenderer m_skyboxRenderer;
	EntityRenderer m_entityRenderer;
	TerrainRenderer m_terrainRenderer;
	StaticShader m_shader;
	TerrainShader m_terrainShader;

	std::map<TexturedModel, std::list<Entity>> entities;
};

#endif // !MASTERRENDERER_H