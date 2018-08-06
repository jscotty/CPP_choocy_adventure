#ifndef TERRAIN_H
#define TERRAIN_H

#include "RawModel.h"
#include "ModelTexture.h"
#include "TerrainTexturePack.h"
#include "TerrainTexture.h"
#include "Loader.h"
#include <glm\vec3.hpp>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <string>
#include <math.h> 

class Terrain{
public:
	Terrain(int x, int z, Loader& loader, TerrainTexturePack texturePack, TerrainTexture blendMap);
	~Terrain();

	inline glm::mat4 GetMVP() const {
		glm::mat4 posMatrix = glm::translate(glm::vec3(m_x,0,m_z));

		glm::mat4 rotXMatrix = glm::rotate(0.0f, glm::vec3(1.0, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(0.0f, glm::vec3(0, 1.0, 0));
		glm::mat4 rotZMatrix = glm::rotate(0.0f, glm::vec3(0, 0, 1.0));
		glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;

		glm::mat4 scaleMatrix = glm::scale(glm::vec3(1,1,1));

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline float GetX() { return m_x; }
	inline float GetZ() { return m_z; }
	float GetHeight(float worldX, float worldZ);
	inline RawModel GetModel() { return m_model; }
	inline TerrainTexturePack GetTerrainTexturePack() { return m_texturePack; }
	inline TerrainTexture GetBlendMapTexture() { return m_blendMapTexture; }
private:
	static const int SIZE = 400;
	static const int VERTEX_COUNT = 128;
	static const int MAX_HEIGHT = 40;
	static const int MAX_PIXEL_COLOR = 255;

	RawModel GenerateTerrain(Loader& loader, std::string heightMap);
	float GetHeighti(int x, int z);
	glm::vec3 CalculateNormal(int x, int z);

	float m_x;
	float m_z;
	float m_heights[VERTEX_COUNT][VERTEX_COUNT];
	RawModel m_model;
	TerrainTexturePack m_texturePack;
	TerrainTexture m_blendMapTexture;

	int m_heightMapWidth, m_heightMapHeight, m_heightMapNumComponents;
	unsigned char* m_heightMapImageData;

	float BarryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
};

#endif // !TERRAIN_H