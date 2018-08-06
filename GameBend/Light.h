#ifndef LIGHT_H
#define LIGHT_H

#include <GL\glew.h>
#include <glm\glm.hpp>

class Light {
public:
	Light(glm::vec3 position, glm::vec3 color) : m_position(position), m_color(color), m_attenuation(glm::vec3(1.0f, 0.0f, 0.0f)) {}
	Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation) : m_position(position), m_color(color), m_attenuation(attenuation) {}

	inline glm::vec3& GetPosition() { return m_position; }
	inline glm::vec3& GetColor() { return m_color; }
	inline glm::vec3& GetAttenuation() { return m_attenuation; }
	inline void SetAttenuation(glm::vec3 attenuation) { m_attenuation = attenuation; }
	inline void SetPosition(glm::vec3 position) { m_position = position; }
private:
	glm::vec3 m_position;
	glm::vec3 m_color;
	glm::vec3 m_attenuation;
};

#endif // !LIGHT_H
