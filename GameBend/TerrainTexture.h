#ifndef TERRAINTEXTURE_H
#define TERRAINTEXTURE_H

#include "GL\glew.h"

class TerrainTexture{
public:
	TerrainTexture(GLuint textureID) { m_textureID = textureID; }
	TerrainTexture() { }
	~TerrainTexture() {}

	inline GLuint GetTextureID() { return m_textureID; }
private:
	GLuint m_textureID;
};

#endif // !TERRAINTEXTURE_H