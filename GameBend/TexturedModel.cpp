#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel model, ModelTexture texture) {
	this->m_rawModel = model;
	this->m_texture = texture;
	id = model.GetVaoID();
}

TexturedModel::~TexturedModel(){}
