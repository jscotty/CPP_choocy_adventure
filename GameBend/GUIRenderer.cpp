#include "GUIRenderer.h"
#include <iostream>
#include "glm\glm.hpp"
#include <vector>
#include "Maths.h"

GUIRenderer::GUIRenderer(Loader& loader) {
	std::vector<glm::vec2> positions = {
		glm::vec2(-1, 1),
		glm::vec2(-1, -1),
	    glm::vec2(1, 1),
		glm::vec2(1, -1)
	};
	
	m_quad = loader.LoadToVAO(positions);
	m_shader.BindAttributes();
}

void GUIRenderer::Render(std::list<GUITexture>& guis) {

	m_shader.Bind();
	glBindVertexArray(m_quad.GetVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	for (std::list<GUITexture>::iterator it = guis.begin(); it != guis.end(); it++) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (*it).GetTextureID());
		glm::mat4 matrix = Maths::CreateTransformationMatrix((*it).GetPosition(), (*it).GetScale());
		m_shader.LoadTransformationMatrix(matrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, m_quad.GetVertexCount());
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	m_shader.Unbind();
}

GUIRenderer::~GUIRenderer() {}