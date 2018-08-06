#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <iostream>
#include "Display.h"
#include "Entity.h"
#include "Terrain.h"

class Camera {
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar, Entity& entity) : m_focusedObject(entity) {
		m_projection = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(0.0f, 0.0f, 1.0f);
		m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_focusedObject = entity;
	}

	void Move(Terrain& terrain);

	inline glm::mat4 GetViewMatrix() const {
		/*glm::mat4 viewMatrix;

		glm::mat4 rotXMatrix = glm::rotate(glm::radians(m_pitch), glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(glm::radians(m_yaw), glm::vec3(0, 1, 0));
		glm::mat4 rotMatrix = rotXMatrix * rotYMatrix;

		glm::vec3 negativeCameraPos(-m_position.x, -m_position.y, -m_position.z);
		glm::mat4 posMatrix = glm::translate(negativeCameraPos);
		return posMatrix*rotMatrix;*/
		return m_projection * glm::lookAt(m_position, m_focusedObject.GetPosition(), m_up);
	}

	inline glm::mat4 GetViewMatrixZero() const {
		return m_projection * glm::lookAt(m_rot, glm::vec3(0, 0, 0), m_up);
	}
protected:
private:
	const float MAX_PITCH = 260.0F;
	const float MIN_PITCH = -100.0F;

	void CalculateZoom();
	void CalculatePitch();
	void CalculateAngleAroundObject();
	void CalculateAngleCameraPosition(float horizontalDistance, float verticalDistance, float terrainHeight);
	float CalculateHorizontalDistance();
	float CalculateVerticalDistance();

	Entity& m_focusedObject;

	glm::mat4 m_projection;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	glm::vec3 m_rot;

	float m_pitch = 20;
	float m_yaw = 0;
	float m_roll;
	float m_distanceFromObject = 30.0f;
	float m_angleAroundObject = 0.0f;
};

#endif // !CAMERA_H