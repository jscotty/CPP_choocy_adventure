#include "WaterRenderer.h"
#include <iostream>

WaterRenderer::WaterRenderer(Loader& loader, WaterShader& shader) : m_waterShader(shader) {
	SetUpVAO(loader);
}

void WaterRenderer::SetUpVAO(Loader& loader) {
	std::vector<glm::vec2> vertices = {
		glm::vec2(-1,-1),
		glm::vec2(-1, 1),
		glm::vec2(1,-1),
		glm::vec2(1,-1),
		glm::vec2(-1 ,1),
		glm::vec2(1, 1),
	};

	m_quad = loader.LoadToVAO(vertices);
}

void WaterRenderer::Render(std::vector<WaterTile> waterTiles, Camera& camera) {
	PrepareRender(camera);

	for (std::vector<WaterTile>::iterator i = waterTiles.begin(); i != waterTiles.end(); i++)
	{
		m_waterShader.LoadModelMatrix((*i).GetMVP());

		glDrawArrays(GL_TRIANGLES, 0, m_quad.GetVertexCount());
	}

	Unbind();
}

void WaterRenderer::PrepareRender(Camera& camera) {
	m_waterShader.Bind();
	m_waterShader.LoadViewMatrix(camera.GetViewMatrix());
	glBindVertexArray(m_quad.GetVaoID());
	glEnableVertexAttribArray(0);
}

void WaterRenderer::Unbind() {
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	m_waterShader.Unbind();
}


WaterRenderer::~WaterRenderer() { }
