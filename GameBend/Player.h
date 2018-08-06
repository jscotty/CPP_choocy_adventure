#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "TexturedModel.h"
#include <glm\glm.hpp>
#include "Terrain.h"

class Player : public Entity{
public:
	Player(TexturedModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Entity(model, position, rotation, scale) {
		this->m_model = model;
		this->m_position = position;
		this->m_rotation = rotation;
		this->m_scale = scale;
	}
	Player(TexturedModel model, int textureIndex, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Entity(model, textureIndex, position, rotation, scale) {
		this->m_model = model;
		this->m_position = position;
		this->m_rotation = rotation;
		this->m_scale = scale;
	}

	void Move(Terrain& terrain);
	void CheckInput();

	~Player();

private:
	const float SPEED = 20;
	const float ROTATION_SPEED = 5.0f;
	const float GRAVITY = -50.0f;
	const float JUMP_POWER = 20.0f;

	float m_currentSpeed = 0.0f;
	float m_currentRotationSpeed = 0.0f;
	float m_currentJumpPower;
	bool m_isInAir = false;

	TexturedModel m_model;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};

#endif // !PLAYER_H