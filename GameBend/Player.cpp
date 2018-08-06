#include "Player.h"
#include <iostream>
#include "Display.h"

void Player::Move(Terrain& terrain) {
	CheckInput();
	Entity::IncreaseRotation(glm::vec3(0, m_currentRotationSpeed * Display::GetDeltaTime(), 0));

	float distance = m_currentSpeed * Display::GetDeltaTime();
	float dX = distance * sin(Entity::GetRotation().y);
	float dZ = distance * cos(Entity::GetRotation().y);
	Entity::IncreasePosition(glm::vec3(dX, 0, dZ));

	m_currentJumpPower += GRAVITY * Display::GetDeltaTime();
	Entity::IncreasePosition(glm::vec3(0, m_currentJumpPower *Display::GetDeltaTime(), 0));
	m_position = Entity::GetPosition();
	float terrainHeight = terrain.GetHeight(m_position.x, m_position.z);
	if (Entity::GetPosition().y < terrainHeight) {
		Entity::SetYPos(terrainHeight);
		m_isInAir = false;
	} else {
		m_isInAir = true;
	}
}

void Player::CheckInput() {
	int keyDownKey = 0;
	if (Display::GetKeyDown(SDLK_w)) {
		m_currentSpeed = SPEED;
	} else if (Display::GetKeyDown(SDLK_s)) {
		m_currentSpeed = -SPEED;
	} else {
		m_currentSpeed = 0.0f;
	}

	if (Display::GetKeyDown(SDLK_a)) {
		m_currentRotationSpeed = ROTATION_SPEED;
	} else if (Display::GetKeyDown(SDLK_d)) {
		m_currentRotationSpeed = -ROTATION_SPEED;
	} else {
		m_currentRotationSpeed = 0.0f;
	}

	if (Display::GetKeyDown(SDLK_SPACE) && !m_isInAir) {
		m_currentJumpPower = JUMP_POWER;
	}
}

Player::~Player(){}