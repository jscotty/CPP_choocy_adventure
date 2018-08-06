#include "Camera.h"
#include "sdl\SDL.h"
#include <iostream>

void Camera::Move(Terrain& terrain) {
	CalculateZoom();
	if (Display::GetMouseDown(SDL_BUTTON_LEFT)) {
		CalculatePitch();
		CalculateAngleAroundObject();
	}
	float horizontalDistance = CalculateHorizontalDistance();
	float verticalDistance = CalculateVerticalDistance();
	CalculateAngleCameraPosition(horizontalDistance, verticalDistance, terrain.GetHeight(m_position.x, m_position.z)+2.0f);
}


void Camera::CalculateZoom() {
	//TODO: scroll
}

void Camera::CalculatePitch() {
	float pitchChange = Display::GetMouseDelta().y *0.1f;
	m_pitch -= pitchChange;
	if (m_pitch < MIN_PITCH) m_pitch = MIN_PITCH;
	else if (m_pitch > MAX_PITCH) m_pitch = MAX_PITCH;
	//(m_pitch < MIN_PITCH) ? m_pitch = MIN_PITCH : (m_pitch > MAX_PITCH) ? m_pitch = MAX_PITCH : m_pitch -= pitchChange;
}

void Camera::CalculateAngleAroundObject() {
	float angleChange = Display::GetMouseDelta().x *0.3f;
	m_angleAroundObject -= angleChange;
}

void Camera::CalculateAngleCameraPosition(float horizontalDistance, float verticalDistance, float terrainHeight) {
	float theta = m_focusedObject.GetRotation().y + m_angleAroundObject;
	float offsetX = (float)(horizontalDistance * sin(glm::radians(theta)));
	float offsetZ = (float)(horizontalDistance * cos(glm::radians(theta)));
	m_position.x = m_focusedObject.GetPosition().x - offsetX;
	m_position.z = m_focusedObject.GetPosition().z - offsetZ;

	float calcY = m_focusedObject.GetPosition().y + verticalDistance;
	m_rot.y = calcY;
	m_position.y = m_rot.y;
	m_rot.x = offsetX; m_rot.z = offsetZ;
}

float Camera::CalculateHorizontalDistance() {
	return (float)(m_distanceFromObject * cos(glm::radians(m_pitch)));
}

float Camera::CalculateVerticalDistance() {
	return (float)(m_distanceFromObject * sin(glm::radians(m_pitch)));
}