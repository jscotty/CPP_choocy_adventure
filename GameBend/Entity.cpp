#include "Entity.h"

Entity::Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
	this->m_model = model;
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_scale = scale;
}

Entity::Entity(TexturedModel model, int index, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
	this->m_model = model;
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_scale = scale;
	this->m_textureIndex = index;
}

void Entity::IncreasePosition(glm::vec3 direction) {
	this->m_position += direction;
}

void Entity::IncreaseRotation(glm::vec3 direction) {
	this->m_rotation += direction;
}

Entity::~Entity(){

}
