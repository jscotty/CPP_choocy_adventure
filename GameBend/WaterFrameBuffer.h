#ifndef WATERFRAMEBUFFER_H
#define WATERFRAMEBUFFER_H

#include "GL\glew.h"
#include "glm\glm.hpp"

class WaterFrameBuffer{
public:
	WaterFrameBuffer();
	~WaterFrameBuffer();

	void BindReflectionFrameBuffer();
	void BindRefractionFrameBuffer();
	void UnbindCurrentFrameBuffer();

	GLuint GetReflectionTexture() { return m_reflectionTexture; }
	GLuint GetRefractionTexture() { return m_refractionTexture; }
	GLuint GetRefractionDepthTexture() { return m_refractionDepthTexture; }

protected:
	const int REFLECTION_WIDTH = 200;
	const int REFRACTION_WIDTH = 800;
private:
	const int REFLECTION_HEIGHT = 150;
	const int REFRACTION_HEIGHT = 600;

	GLuint m_reflectionFrameBuffer;
	GLuint m_reflectionTexture;
	GLuint m_reflectionDepthBuffer;

	GLuint m_refractionFrameBuffer;
	GLuint m_refractionTexture;
	GLuint m_refractionDepthTexture;

	void InitialiseReflectionFrameBuffer();
	void InitialiseRefractionFrameBuffer();

	void BindFrameBufferReflection(int width, int height);
	void BindFrameBufferRefraction(int width, int height);

	void CreateReflectionFrameBuffer();
	void CreateRefractionFrameBuffer();

	void CreateReflectionTextureAttachment(int width, int height);
	void CreateRefractionTextureAttachment(int width, int height);

	void CreateRefractionDepthTextureAttachment(int width, int height);

	void CreateReflectionDepthBufferAttachment(int width, int height);
};

#endif // !WATERFRAMEBUFFER_H