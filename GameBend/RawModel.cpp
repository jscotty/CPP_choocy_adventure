#include "RawModel.h"

RawModel::RawModel(const GLuint vaoID, unsigned int vertexCount){
	this->vaoID = vaoID;
	this->vertexCount = vertexCount;
}
RawModel::RawModel(){}

RawModel::~RawModel(){}