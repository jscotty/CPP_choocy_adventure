#ifndef ENTITY_H
#define ENTITY_H

#include "TexturedModel.h"
#include <glm\vec3.hpp>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <iostream>

class Entity{
public:
	Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Entity(TexturedModel model, int index, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Entity() {}

	void IncreasePosition(glm::vec3 direction);
	void IncreaseRotation(glm::vec3 direction);

	~Entity();

	inline glm::mat4 GetMVP() const {
		glm::mat4 posMatrix = glm::translate(m_position);

		glm::mat4 rotXMatrix = glm::rotate(m_rotation.x, glm::vec3(1.0, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(m_rotation.y, glm::vec3(0, 1.0, 0));
		glm::mat4 rotZMatrix = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1.0));
		glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;

		glm::mat4 scaleMatrix = glm::scale(m_scale);

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline TexturedModel GetModel() { return m_model; }
	inline glm::vec3 GetPosition() { return m_position; }
	inline glm::vec3 GetRotation() { return m_rotation; }
	inline glm::vec3 GetScale() { return m_scale; }
	inline void SetPosition(glm::vec3 position) { m_position = position; }
	inline void SetRotation(glm::vec3 rotation) { m_rotation = rotation; }
	inline void SetScale(glm::vec3 scale) { m_scale = scale; }
	inline void SetXPos(float posX) { m_position.x = posX; }
	inline void SetYPos(float posY) { m_position.y = posY; }
	inline void SetZPos(float posZ) { m_position.z = posZ; }

	float GetTextureXOffset() {
		int collumn = m_textureIndex % m_model.GetTexture().GetNumberOfRows();
		return (float)collumn / (float)m_model.GetTexture().GetNumberOfRows();
	}
	float GetTextureYOffset() {
		int row = m_textureIndex / m_model.GetTexture().GetNumberOfRows();
		return (float)row / (float)m_model.GetTexture().GetNumberOfRows();
	}
protected:

private:
	TexturedModel m_model;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	int m_textureIndex = 0;
};

#endif // !ENTITIE_H