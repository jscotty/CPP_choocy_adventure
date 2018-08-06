#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include "RawModel.h"
#include "Entity.h"
#include "Loader.h"
#include "GUITexture.h"
#include <list>
#include <iostream>
#include "GUIShader.h"
#include "GL\glew.h"

class GUIRenderer {
public:
	GUIRenderer(Loader& loader);
	~GUIRenderer();

	//void Render(Entity entity, StaticShader& shader, Camera& camera);
	void Render(std::list<GUITexture>& guis);
private:
	RawModel m_quad;

	glm::mat4 m_projectionMatrix;
	GUIShader m_shader;
};

#endif // !GUIRENDERER_H
