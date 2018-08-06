#include "EntityRenderer.h"
#include "MasterRenderer.h"

void EntityRenderer::Render(std::map<TexturedModel, std::list<Entity>>& entities, Entity& player) {
	for (std::map<TexturedModel, std::list<Entity>>::iterator it = entities.begin(); it != entities.end(); it++) {
		TexturedModel texturedModel = it->first;
		//std::cout << data.model.GetRawModel().GetVaoID() << std::endl;
		PrepareModel(texturedModel, player.GetPosition());
		//std::cout << "vaoid "<< texturedModel.GetRawModel().GetVaoID() << " size "<< data.entities.size()<< std::endl;
		for (std::list<Entity>::iterator e_it = it->second.begin(); e_it != it->second.end(); e_it++) {
			PrepareInstance(*e_it);

			glDrawElements(GL_TRIANGLES, texturedModel.GetRawModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
		}
		UnbindTexturedModel();
	}
}

void EntityRenderer::PrepareModel(TexturedModel texturedModel, glm::vec3 originCurvePosition) {
	RawModel model = texturedModel.GetRawModel();
	ModelTexture texture = texturedModel.GetTexture();

	glBindVertexArray(model.GetVaoID());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	m_shader.LoadNumberOfRows(texture.GetNumberOfRows());
	if (!texture.HasTransparency()) {
		MasterRenderer::DisableCulling();
	}
	m_shader.LoadCurve(originCurvePosition, glm::vec3(1, 0, 1));
	m_shader.LoadSpecular(texture.Shininess(), texture.Reflectivity());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());
}
void EntityRenderer::PrepareInstance(Entity entity) {
	m_shader.LoadTranformationMatrix(entity.GetMVP());
	m_shader.LoadOffset(entity.GetTextureXOffset(), entity.GetTextureYOffset());

}
void EntityRenderer::UnbindTexturedModel() {
	MasterRenderer::EnableCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);
}

EntityRenderer::~EntityRenderer() {}
