#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "RawModel.h"
#include <GL\glew.h>
#include <glm\vec3.hpp>
#include <string>
#include <iostream>
#include "OBJLoader.h"
#include "TextureData.h"


class Vertex {
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord) {
		this->m_pos = pos;
		this->m_texCoord = texCoord;
	}
	Vertex() { } //default constructor

	inline glm::vec3 getPos() { return m_pos; }
	inline glm::vec2 getTexCoord() { return m_texCoord; }
	inline void SetPos(glm::vec3 pos) { this->m_pos = pos; }
	inline void Init(glm::vec3 pos, glm::vec2 texCoord) { this->m_pos = pos; this->m_texCoord = texCoord; }
	inline void SetTexCoord(glm::vec2 texCoord) { this->m_texCoord = texCoord; }
protected:
private:
	glm::vec3 m_pos;
	glm::vec2 m_texCoord;
};

class Loader{
public:
	RawModel LoadToVAO(const std::string& fileName);
	RawModel LoadToVAO(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, glm::vec3* normals, unsigned int numNormals);
	RawModel LoadToVAO(std::vector<glm::vec2> positions);
	RawModel LoadToVAO(std::vector<glm::vec3> positions);
	void InitMesh(IndexedModel model);
	virtual ~Loader();
	GLuint LoadTexture(const std::string& fileName);
	GLuint LoadCubeMap(std::string files[]);
private:
	int CreateVAO();
	void StoreDataInAttributeList(int attributeNumer, int coordinateSize, int bufferIndex, IndexedModel model);
	void StoreDataInAttributeList(int attributeNumer, int coordinateSize, std::vector<glm::vec2> data);
	void StoreDataInAttributeList(int attributeNumer, int coordinateSize, std::vector<glm::vec3> data);
	TextureData DecondeTextureFile(std::string fileName);
	void UnbindVAO();
	void BindIndicesBuffer(IndexedModel model);

/*
	ModelData StoreData(glm::vec3 data[]);
	ModelData StoreData(unsigned int data[]);
*/

	enum {
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NORMAL_VB,
		GUI_DATA_VB,
		NUM_BUFFERS 
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	GLuint m_texture;
	GLuint m_cubeMap;

	//std::list<GLuint> m_vaos; //storage
	//std::list<GLuint> m_vbos; //storage
	
	unsigned int m_drawCount;
};

#endif // !LOADER_H
