#include "Terrain.h"
#include <glm\glm.hpp>
#include "stb_image.h"

Terrain::Terrain(int x, int z, Loader& loader, TerrainTexturePack texturePack, TerrainTexture blendMap){
	this->m_texturePack = texturePack;
	this->m_blendMapTexture = blendMap;
	this->m_x = (float)x*(float)SIZE;
	this->m_z = (float)z*(float)SIZE;
	this->m_model = GenerateTerrain(loader, "./res/heightmap2.png");
}

RawModel Terrain::GenerateTerrain(Loader& loader, std::string heightMap) {
	m_heightMapImageData = stbi_load(heightMap.c_str(), &m_heightMapWidth, &m_heightMapHeight, &m_heightMapNumComponents, STBI_rgb);
	int* ptr;
	int n = m_heightMapWidth;
	ptr = new int[n];
	unsigned int indices[6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)] = {};
	int vertexPointer = 0;
	Vertex vertexArray[(VERTEX_COUNT * VERTEX_COUNT)] = {};
	glm::vec3 normalArray[(VERTEX_COUNT * VERTEX_COUNT)] = {};
	for (size_t i = 0; i < VERTEX_COUNT; i++) {
		for (size_t j = 0; j < VERTEX_COUNT; j++) {
			float vertexHeight = GetHeighti(j, i);
			m_heights[j][i] = vertexHeight;
			vertexArray[vertexPointer].Init(
			glm::vec3(
				(float)j / ((float)VERTEX_COUNT - 1) * SIZE,
				vertexHeight,
				(float)i / ((float)VERTEX_COUNT - 1) * SIZE
			), 
			glm::vec2(
			(float)j / ((float)VERTEX_COUNT - 1),
				(float)i / ((float)VERTEX_COUNT - 1))
			);

			glm::vec3 normal = CalculateNormal(j, i);
			normalArray[vertexPointer].x = normal.x;
			normalArray[vertexPointer].y = normal.y;
			normalArray[vertexPointer].z = normal.z;
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (size_t gz = 0; gz<VERTEX_COUNT - 1; gz++) {
		for (size_t gx = 0; gx<VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	return loader.LoadToVAO(vertexArray, sizeof(vertexArray) / sizeof(vertexArray[0]), indices, sizeof(indices) / sizeof(indices[0]), normalArray, sizeof(normalArray)/ sizeof(normalArray[0]));
}

glm::vec3 Terrain::CalculateNormal(int x, int z) {
	float heightL = GetHeighti(x - 1, z);
	float heightR = GetHeighti(x + 1, z);
	float heightU = GetHeighti(x, z - 1);
	float heightD = GetHeighti(x, z + 1);
	glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);

	glm::normalize(normal);
	
	return normal;
}


float Terrain::GetHeighti(int x, int z) {
	if (x<0 || x>m_heightMapHeight || z<0 || z>m_heightMapHeight) {
		//out of bounds
		return 0;
	}
	float desiredHeight = (float)m_heightMapImageData[(x*m_heightMapWidth+z)*3];
	desiredHeight /= 255;
	desiredHeight = ((desiredHeight + 0.5f) - 1.0f) * 2.0f;
	desiredHeight *= MAX_HEIGHT;

	return desiredHeight;
}

float Terrain::GetHeight(float worldX, float worldZ) {
	float x = worldX - m_x;
	float z = worldZ - m_z;
	float gridSquareSize = SIZE / (float)(VERTEX_COUNT - 1.0f);
	int gridX = (int)(floor(x / gridSquareSize));
	int gridZ = (int)(floor(z / gridSquareSize));
	if (gridX >= (VERTEX_COUNT - 1) || gridZ >= (VERTEX_COUNT - 1) || gridX < 0 || gridZ < 0) {
		return 0.0f;
	}
	float xCoord = fmodf(x, gridSquareSize);
	xCoord /= gridSquareSize;
	float zCoord = fmodf(z, gridSquareSize);
	zCoord /= gridSquareSize;

	float height;
	if (xCoord >= (1 - zCoord)) {
		return BarryCentric(glm::vec3(0, m_heights[gridX][gridZ], 0), glm::vec3(1, m_heights[gridX + 1][gridZ], 0), glm::vec3(0, m_heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
	}
	else {
		return BarryCentric(glm::vec3(1, m_heights[gridX + 1][gridZ], 0), glm::vec3(1,
			m_heights[gridX + 1][gridZ + 1], 1), glm::vec3(0,
				m_heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
	}
	return height;
}

float Terrain::BarryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

Terrain::~Terrain(){}
