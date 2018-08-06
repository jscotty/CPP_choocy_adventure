#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H

#include "RawModel.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Camera.h"
#include <map>
#include <list>
#include <iostream>
#include "Maths.h"
#include "ModelRenderData.h"

class EntityRenderer {
public:
	EntityRenderer(StaticShader& shader) { m_shader = shader; }
	EntityRenderer() {}
	~EntityRenderer();

	void Init(StaticShader& shader) { m_shader = shader; }

	//void Render(Entity entity, StaticShader& shader, Camera& camera);
	void Render(std::map<TexturedModel, std::list<Entity>>& entities, Entity& player);
private:
	const float FOV = 70;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 1000.0f;

	void PrepareModel(TexturedModel texturedModel, glm::vec3 originCurvePosition);
	void PrepareInstance(Entity entity);
	void UnbindTexturedModel();

	glm::mat4 m_projectionMatrix;
	StaticShader m_shader;
};

#endif // !ENTITYRENDERER_H
