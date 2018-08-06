#ifndef WATERSHADER_H
#define WATERSHADER_H

#include "ShaderProgram.h"
#include <string>
#include <iostream>
#include <gl\glew.h>
#include "Light.h"
#include <glm\gtx\transform.hpp>
#include "Display.h"

class WaterShader : public ShaderProgram {
private:
	float rotationSpeed = 0.01f;
	float currentRotation = 0.0f;

	GLuint location_viewMatrix;
	GLuint location_modelMatrix;

public:
	WaterShader() : ShaderProgram("./shaders/WaterShader") { }
	~WaterShader() {}
	void BindAttributes() {
		ShaderProgram::BindAttribute(0, "position");

		ShaderProgram::Link();

		GetAllUniforms();
	}
	void LoadViewMatrix(glm::mat4 matrix) {
		ShaderProgram::LoadMatrix4(location_viewMatrix, matrix);
	}
	void LoadModelMatrix(glm::mat4 matrix) {
		ShaderProgram::LoadMatrix4(location_modelMatrix, matrix);
	}
protected:
	void GetAllUniforms() {
		location_viewMatrix = ShaderProgram::GetUniformLocation("viewMatrix");
		location_modelMatrix = ShaderProgram::GetUniformLocation("modelMatrix");
	}
};

#endif // !WATERSHADER_H