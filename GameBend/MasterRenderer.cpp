#include "MasterRenderer.h"
#include <algorithm>
#include <iostream>

void MasterRenderer::RenderScene(std::vector<Entity> entities, std::vector<Terrain> terrains, Light lightSource, Camera camera, Entity& player) {
	ProcessEntity(player);
	
	for (std::vector<Entity>::iterator i = entities.begin(); i != entities.end(); i++) {
		ProcessEntity((*i));
	}
	for (std::vector<Terrain>::iterator i = terrains.begin(); i != terrains.end(); i++) {
		ProcessTerrain((*i));
	}

	Render(lightSource, camera, player);
}

void MasterRenderer::Render(Light sun, Camera camera, Entity& player) {
	m_shader.Bind();
	m_shader.LoadLight(sun);
	//shader.LoadProjectionMatrix(camera.GetProjectionMatrix());
	m_shader.LoadViewMatrix(camera.GetViewMatrix());

	m_shader.LoadSkyColor(glm::vec3(0.2f, 0.2f, 0.2f));

	m_entityRenderer.Render(entities, player);
	m_shader.Unbind();

	m_terrainShader.Bind();
	m_terrainShader.LoadLight(sun);
	//tShader.LoadProjectionMatrix(camera.GetProjectionMatrix());
	m_terrainShader.LoadViewMatrix(camera.GetViewMatrix());
	m_terrainShader.LoadSkyColor(glm::vec3(0.2f, 0.2f, 0.2f));

	m_terrainRenderer.Render(m_terrains, player);
	m_terrainShader.Unbind();

	m_skyboxRenderer.Render(camera);

	entities.clear();
	m_terrains.clear();
}

void MasterRenderer::EnableCulling() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MasterRenderer::DisableCulling() {
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::ProcessTerrain(Terrain& terrain) {
	m_terrains.push_back(terrain);
}

void MasterRenderer::ProcessEntity(Entity& entity) {
	TexturedModel model = entity.GetModel();
	std::map<TexturedModel, std::list<Entity>>::iterator batch = entities.find(model);
	if (batch == entities.end()) { //not found
		std::list<Entity> newBatch;
		newBatch.push_back(entity);
		entities[model] = newBatch;
	} else { //found
		entities[model].push_back(entity);
	}
}

MasterRenderer::MasterRenderer(Loader& loader) : m_skyboxRenderer(SkyboxRenderer(loader)) {
	m_shader.BindAttributes();
	m_entityRenderer.Init(m_shader);
	m_terrainShader.BindAttributes();
	m_terrainRenderer.Init(m_terrainShader);
}

MasterRenderer::~MasterRenderer(){
	entities.clear();
	m_terrains.clear();
}