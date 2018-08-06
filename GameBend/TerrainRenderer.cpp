#include "TerrainRenderer.h"
#include "Maths.h"
#include "glm\glm.hpp"
#include <iostream>

TerrainRenderer::TerrainRenderer(TerrainShader& shader) { 
	m_shader = shader;
}

void TerrainRenderer::Render(std::list<Terrain>& terrains, Entity& player) {
	for (std::list<Terrain>::iterator it = terrains.begin(); it != terrains.end(); it++) {
		PrepareTerrain(*it, player.GetPosition());
		LoadModelMatrix(*it);

		glDrawElements(GL_TRIANGLES, it->GetModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
	}
	UnbindTerrain();
}

void TerrainRenderer::PrepareTerrain(Terrain terrain, glm::vec3 originCurvePosition) {
	RawModel model = terrain.GetModel();

	glBindVertexArray(model.GetVaoID());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	bool once = true;
	if (once) {
		m_shader.ConnectTextureUnits();
		once = false;
	}
	BindTextures(terrain);
	m_shader.LoadCurve(originCurvePosition, glm::vec3(1,0,1));
	m_shader.LoadSpecular(1,0);
}

void TerrainRenderer::BindTextures(Terrain terrain) {
	TerrainTexturePack pack = terrain.GetTerrainTexturePack();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pack.GetBackgroundTexture().GetTextureID());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pack.GetRTexture().GetTextureID());

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, pack.GetGTexture().GetTextureID());

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, pack.GetBTexture().GetTextureID());

	TerrainTexture blend = terrain.GetBlendMapTexture();
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, blend.GetTextureID());

}

void TerrainRenderer::LoadModelMatrix(Terrain terrain) {
	m_shader.LoadTranformationMatrix(terrain.GetMVP());

}
void TerrainRenderer::UnbindTerrain() {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);
}

TerrainRenderer::~TerrainRenderer(){}
