#ifndef GUITEXTURE
#define GUITEXTURE

#include "glm\glm.hpp"
#include "GL\glew.h"

class GUITexture {
public:
	GUITexture(GLuint texture, glm::vec2 position , glm::vec2 scale) : m_textureID(texture), m_position(position), m_scale(scale) {}

	inline GLuint GetTextureID() { return m_textureID; }
	inline glm::vec2 GetPosition() { return m_position; }
	inline glm::vec2 GetScale() { return m_scale; }
private:
	GLuint m_textureID;
	glm::vec2 m_position;
	glm::vec2 m_scale;

};
#endif // !GUITEXTURE
