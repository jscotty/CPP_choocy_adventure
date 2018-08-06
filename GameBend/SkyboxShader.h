#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H

#include "ShaderProgram.h"
#include <string>
#include <iostream>
#include <gl\glew.h>
#include "Light.h"
#include <glm\gtx\transform.hpp>
#include "Display.h"

class SkyboxShader : public ShaderProgram {
private:
	float rotationSpeed = 0.01f;
	float currentRotation = 0.0f;

	GLuint location_viewMatrix;
	GLuint location_fogColor;

public:
	SkyboxShader() : ShaderProgram("./shaders/Skybox") { }
	~SkyboxShader() {}
	void BindAttributes() {
		ShaderProgram::BindAttribute(0, "position");
		ShaderProgram::BindAttribute(1, "textureCoords");
		ShaderProgram::BindAttribute(2, "normal");

		ShaderProgram::Link();

		GetAllUniforms();
	}
	void LoadViewMatrix(glm::mat4 matrix) {
		currentRotation += rotationSpeed*Display::GetDeltaTime();
		glm::mat4 rotation = glm::rotate(currentRotation, glm::vec3(0, 1.0, 0));
		matrix = matrix * rotation;
		ShaderProgram::LoadMatrix4(location_viewMatrix, matrix);
	}
	void LoadFog(float r, float g, float b) {
		ShaderProgram::LoadVector3(location_fogColor, glm::vec3(r, g, b));
	}
	void LoadFog(glm::vec3 color) {
		ShaderProgram::LoadVector3(location_fogColor, color);
	}
protected:
	void GetAllUniforms() {
		location_viewMatrix = ShaderProgram::GetUniformLocation("viewMatrix");
		location_fogColor = ShaderProgram::GetUniformLocation("fogColor");
	}
};

#endif // !SKYBOXSHADER_H