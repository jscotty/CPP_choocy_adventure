#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "RawModel.h"
#include "ModelTexture.h"
#include "GL\glew.h"

class TexturedModel{
public:
	TexturedModel(RawModel model, ModelTexture texture);
	TexturedModel() {}//default constructor.
	~TexturedModel();

	inline RawModel GetRawModel() { return m_rawModel; }
	inline ModelTexture GetTexture() { return m_texture; }

	bool operator < (const TexturedModel& rhs)const {
		return id < rhs.id;
	}
private:
	GLuint id;
	RawModel m_rawModel;
	ModelTexture m_texture;
};

#endif // !TEXTUREDMODEL_H