#ifndef RAWMODEL_H
#define RAWMODEL_H

#include "glm\glm.hpp"
#include "GL\glew.h"

class RawModel {
public:
	RawModel(const GLuint vaoID, unsigned int vertexCount);
	RawModel();
	~RawModel();

	inline GLuint GetVaoID() { return vaoID; }
	inline unsigned int GetVertexCount() { return vertexCount; }
protected:
private:

	GLuint vaoID;
	unsigned int vertexCount;
};

#endif // !RAWMODEL_H
