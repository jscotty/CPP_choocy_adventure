#ifndef WATERTILE_H
#define WATERTILE_H

#include <iostream>
#include <glm\vec3.hpp>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class WaterTile {
public:
	WaterTile(float x, float z, float height) {
		this->m_x = x;
		this->m_z = z;
		this->m_height = height;
	}

	inline glm::mat4 GetMVP() {
		glm::mat4 posMatrix = glm::translate(glm::vec3(m_x,m_height,m_z));

		glm::mat4 rotXMatrix = glm::rotate(0.0f, glm::vec3(1.0, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(0.0f, glm::vec3(0, 1.0, 0));
		glm::mat4 rotZMatrix = glm::rotate(0.0f, glm::vec3(0, 0, 1.0));
		glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;

		glm::mat4 scaleMatrix = glm::scale(glm::vec3(SIZE,SIZE,SIZE));

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline float GetX() { return m_x; }
	inline float GetZ() { return m_z; }
	inline float GetHeight() { return m_height; }

private:
	const float SIZE = 200.0f;
	float m_x;
	float m_z;
	float m_height;

};

#endif // !WATERTILE_H
