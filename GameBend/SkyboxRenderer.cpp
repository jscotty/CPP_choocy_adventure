#include "SkyboxRenderer.h"
#include <iostream>

SkyboxRenderer::SkyboxRenderer(Loader& loader) {
	m_cube = loader.LoadToVAO(m_vertices);
	m_texture = loader.LoadCubeMap(files);
	m_shader.BindAttributes();
}

void SkyboxRenderer::Render(Camera& camera) {
	m_shader.Bind();
	m_shader.LoadViewMatrix(camera.GetViewMatrixZero());
	m_shader.LoadFog(0.2f, 0.2f, 0.2f);
	glBindVertexArray(m_cube.GetVaoID());
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	glDrawArrays(GL_TRIANGLES, 0, m_cube.GetVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	m_shader.Unbind();
}

SkyboxRenderer::~SkyboxRenderer() {}