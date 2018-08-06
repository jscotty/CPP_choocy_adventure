#include "Loader.h"
#include <cassert>
#include <iostream>
#include <stdio.h>

#include "stb_image.h"

RawModel Loader::LoadToVAO(const std::string& fileName) {
	GLuint vaoID = CreateVAO();
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);

	return RawModel(vaoID, model.indices.size());
}

RawModel Loader::LoadToVAO(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, glm::vec3* normals, unsigned int numNormals) {
	GLuint vaoID = CreateVAO();

	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++) {
		model.positions.push_back(vertices[i].getPos());
		model.texCoords.push_back(vertices[i].getTexCoord());
	}

	for (unsigned int i = 0; i < numIndices; i++) {
		model.indices.push_back(indices[i]);
	}

	for (unsigned int i = 0; i < numNormals; i++) {
		model.normals.push_back(normals[i]);
	}

	InitMesh(model);

	return RawModel(vaoID, numIndices);
}

RawModel Loader::LoadToVAO(std::vector<glm::vec2> positions) {
	GLuint vaoID = CreateVAO();
	StoreDataInAttributeList(0, 2, positions);
	UnbindVAO();

	return RawModel(vaoID, positions.size());
}

RawModel Loader::LoadToVAO(std::vector<glm::vec3> positions) {
	GLuint vaoID = CreateVAO();
	StoreDataInAttributeList(0, 3, positions);
	UnbindVAO();

	return RawModel(vaoID, positions.size());
}

void Loader::InitMesh(IndexedModel model) {
	StoreDataInAttributeList(0, 3, POSITION_VB, model);
	StoreDataInAttributeList(1, 2, TEXCOORD_VB, model);
	StoreDataInAttributeList(2, 3, NORMAL_VB, model);
	BindIndicesBuffer(model);
	UnbindVAO();
}

GLuint Loader::LoadTexture(const std::string& fileName) {
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

	if (imageData == NULL)
		std::cerr << "Texture loading failed! " << fileName << std::endl;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);

	return m_texture;
}

GLuint Loader::LoadCubeMap(std::string files[]) {
	glGenTextures(1, &m_cubeMap);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMap);

	int width, height, numComponents;
	unsigned char* imageData;
	std::cout << (sizeof(*files)/sizeof(files)) << std::endl;
	for (GLuint i = 0; i < 6; i++) {
		std::string fileName = "./res/skybox/" + files[i] + ".png";
		imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);
		if (imageData == NULL)std::cout << "errorrr" << std::endl;
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData
		);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	std::cout << m_cubeMap << std::endl;
	return m_cubeMap;
}

int Loader::CreateVAO() {
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	std::cout << m_vertexArrayObject << " create vbotje" << std::endl;
	return m_vertexArrayObject;
}

TextureData Loader::DecondeTextureFile(std::string fileName) {
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

	if (imageData == NULL)
		std::cerr << "Texture decoding failed! " << fileName << std::endl;

	TextureData data(width, height, numComponents, imageData);
	stbi_image_free(imageData);
	return data;
}

void Loader::StoreDataInAttributeList(int attributeNumber, int coordinateSize, int bufferIndex, IndexedModel model) {

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[bufferIndex]);
	switch (bufferIndex) {
	case POSITION_VB:
		glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
		break;
	case TEXCOORD_VB:
		glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
		break;
	case NORMAL_VB:
		glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
		break;
	default:
		break;
	}

	glEnableVertexAttribArray(attributeNumber);
	//glEnableVertexAttribArray(0);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::StoreDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<glm::vec2> data) {
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data[0]), &data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(attributeNumber);
	//glEnableVertexAttribArray(0);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::StoreDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<glm::vec3> data) {
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data[0]), &data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(attributeNumber);
	//glEnableVertexAttribArray(0);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::BindIndicesBuffer(IndexedModel model) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

}
//
//ModelData Loader::StoreData(glm::vec3 data[]) {
//	ModelData model;
//	for (unsigned int i = 0; i < sizeof(data); i++) {
//		model.data.push_back(data[i]);
//	}
//
//	return model;
//}
//ModelData Loader::StoreData(unsigned int data[]) {
//	ModelData model;
//	for (unsigned int i = 0; i < sizeof(data); i++) {
//		model.indices.push_back(data[i]);
//	}
//	return model;
//}

void Loader::UnbindVAO() {
	glBindVertexArray(0);
}

Loader::~Loader() {
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	glDeleteTextures(1, &m_texture);
}