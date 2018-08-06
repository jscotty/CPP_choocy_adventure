#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H

#include "TerrainShader.h"
#include "Terrain.h"
#include "TexturedModel.h"
#include "TerrainTexture.h"
#include "TerrainTexturePack.h"
#include <list>
#include "Entity.h"

class TerrainRenderer{
public:
	TerrainRenderer(TerrainShader& shader);
	TerrainRenderer() {}
	~TerrainRenderer();

	void Init(TerrainShader& shader) { m_shader = shader; }
	void Render(std::list<Terrain>& terrains, Entity& player);
private:
	void PrepareTerrain(Terrain terrain, glm::vec3 originCurvePosition);
	void BindTextures(Terrain terrain);
	void LoadModelMatrix(Terrain terrain);
	void UnbindTerrain();

	TerrainShader m_shader;
};

#endif // !TERRAINRENDERER_H