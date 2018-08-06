#ifndef WATERRENDERER_H
#define WATERRENDERER_H

#include "WaterShader.h"
#include "WaterTile.h"
#include "Camera.h"
#include "Loader.h"
#include "GL\glew.h"
#include "glm\glm.hpp"

class WaterRenderer
{
public:
	WaterRenderer(Loader& loader, WaterShader& shader);
	~WaterRenderer();

	void Init(WaterShader& shader) { }
	void Render(std::vector<WaterTile> waterTiles, Camera& camera);

private:
	void PrepareRender(Camera& camera);
	void Unbind();
	void SetUpVAO(Loader& loader);
	WaterShader& m_waterShader;
	RawModel m_quad;
};

#endif // !WATERRENDERER_H