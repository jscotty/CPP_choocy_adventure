#ifndef MODELRENDERDATA_H
#define MODELRENDERDATA_H

#include "TexturedModel.h"
#include "Entity.h"
#include <list>

struct ModelRenderData {
public:
	ModelRenderData(TexturedModel& model, std::list<Entity>& entities) : model(model), entities(entities) {}
	TexturedModel& model;
	std::list<Entity>& entities;

	//bool operator<(const ModelRenderData& data) const { return model.GetRawModel().GetVaoID() < data.model.GetRawModel().GetVaoID(); }
};
#endif // !MODELRENDERDATA_H
