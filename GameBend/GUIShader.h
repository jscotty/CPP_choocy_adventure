#pragma once
#include "ShaderProgram.h"
#include <string>
#include <gl\glew.h>
#include "Light.h"
#include <iostream>

class GUIShader : public ShaderProgram {
private:
	GLuint location_tranformMatrix;

public:
	GUIShader() : ShaderProgram("./shaders/GuiShader") { }
	~GUIShader() {}
	void BindAttributes() {
		ShaderProgram::BindAttribute(0, "position");
		ShaderProgram::BindAttribute(1, "textureCoords");
		ShaderProgram::BindAttribute(2, "normal");

		ShaderProgram::Link();

		std::cout << "ey" << std::endl;

		GetAllUniforms();
	}

	void LoadTransformationMatrix(glm::mat4 matrix) {
		ShaderProgram::LoadMatrix4(location_tranformMatrix, matrix);
	}
protected:
	void GetAllUniforms() {
		location_tranformMatrix = ShaderProgram::GetUniformLocation("transformMatrix");
	}
};

