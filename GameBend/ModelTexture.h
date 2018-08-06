#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include <GL\glew.h>
#include <iostream>

class ModelTexture{
public:
	ModelTexture(GLuint texture);
	ModelTexture();
	~ModelTexture();

	inline GLuint GetTextureID() { return this->m_texture; }
	inline float& Shininess() { return m_shininess; }
	inline float& Reflectivity() { return m_reflectivity; }
	inline bool HasTransparency() { return m_hasTransparency; }
	inline void SetTransparency(bool enable) { m_hasTransparency = enable; }
	inline void SetNumberOfRows(int numRows) { m_numRows = numRows; }
	inline int GetNumberOfRows() { return m_numRows; }
	inline bool UseFakeLighting() { return m_useFakeLighting; }
	inline void SetUseFakeLighting(bool enable) { m_useFakeLighting = enable; }
private:
	GLuint m_texture;
	float m_shininess = 1;
	float m_reflectivity = 0;
	int m_numRows = 1;
	bool m_hasTransparency = false;
	bool m_useFakeLighting = false;
};

#endif // !MODELTEXTURE_H