#pragma once
#include "ShaderProgram.h"
#include <string>
#include <iostream>
#include <gl\glew.h>
#include "Light.h"

class StaticShader : public ShaderProgram {
private:
	GLuint location_tranformMatrix;
	//GLuint location_projectionMatrix;
	GLuint location_viewMatrix;
	GLuint location_lightPosition;
	GLuint location_lightColor;
	GLuint location_shininess;
	GLuint location_reflectivity;
	GLuint location_useFakeLighting;
	GLuint location_skyColor;
	GLuint location_numberOfRows;
	GLuint location_offset;
	GLuint location_attenuation;

	GLuint location_curveOrigin;
	GLuint location_scale;
	GLuint location_flatMargin;
	GLuint location_curvature;

public:
	StaticShader() : ShaderProgram("./shaders/BasicShader") { }
	~StaticShader() {}
	void BindAttributes() {
		ShaderProgram::BindAttribute(0, "position");
		ShaderProgram::BindAttribute(1, "textureCoords");
		ShaderProgram::BindAttribute(2, "normal");

		ShaderProgram::Link();

		GetAllUniforms();
	}

	void LoadTranformationMatrix(glm::mat4 matrix) {
		ShaderProgram::LoadMatrix4(location_tranformMatrix, matrix);
	}
	/*void LoadProjectionMatrix(glm::mat4 matrix) {
		ShaderProgram::LoadMatrix4(location_projectionMatrix, matrix);
	}*/
	void LoadViewMatrix(glm::mat4 matrix) {
		ShaderProgram::LoadMatrix4(location_viewMatrix, matrix);
	}
	void LoadLight(Light light) {
		ShaderProgram::LoadVector3(location_lightPosition, light.GetPosition());
		ShaderProgram::LoadVector3(location_lightColor, light.GetColor());
		ShaderProgram::LoadVector3(location_attenuation, light.GetAttenuation());
	}
	void LoadSpecular(float shininess, float reflectivity) {
		ShaderProgram::LoadFloat(location_shininess, shininess);
		ShaderProgram::LoadFloat(location_reflectivity, reflectivity);
	}
	void LoadFakeLighting(bool fakeLighting) {
		ShaderProgram::LoadBoolean(location_useFakeLighting, fakeLighting);
	}
	void LoadSkyColor(glm::vec3 skyColor) {
		ShaderProgram::LoadVector3(location_skyColor, skyColor);
	}
	void loadTextureAtlasCoords(int numberOfRows, glm::vec2 offset) {
		ShaderProgram::LoadInteger(location_numberOfRows, numberOfRows);
		ShaderProgram::LoadVector2(location_offset, offset);
	}
	void LoadNumberOfRows(int numberOfRows) {
		ShaderProgram::LoadInteger(location_numberOfRows, numberOfRows);
	}
	void LoadOffset(float x, float y) {
		ShaderProgram::LoadVector2(location_offset, glm::vec2(x,y));
	}
	void LoadCurve(glm::vec3 origin, glm::vec3 scale) {
		ShaderProgram::LoadVector3(location_curveOrigin, origin);
		ShaderProgram::LoadVector3(location_scale, scale);
		ShaderProgram::LoadFloat(location_curvature, 0.004f);
		ShaderProgram::LoadFloat(location_flatMargin, 5.0f);
	}
protected:
	void GetAllUniforms() {
		location_tranformMatrix = ShaderProgram::GetUniformLocation("transformMatrix");
		//location_projectionMatrix = ShaderProgram::GetUniformLocation("projectionMatrix");
		location_viewMatrix = ShaderProgram::GetUniformLocation("viewMatrix");
		location_lightPosition = ShaderProgram::GetUniformLocation("lightPosition");
		location_lightColor = ShaderProgram::GetUniformLocation("lightColor");
		location_shininess = ShaderProgram::GetUniformLocation("shininess");
		location_reflectivity = ShaderProgram::GetUniformLocation("reflectivity");
		location_useFakeLighting = ShaderProgram::GetUniformLocation("useFakeLighting");
		location_skyColor = ShaderProgram::GetUniformLocation("skyColor");
		location_numberOfRows = ShaderProgram::GetUniformLocation("numberOfRows");
		location_offset = ShaderProgram::GetUniformLocation("offset");
		location_attenuation = ShaderProgram::GetUniformLocation("attenuation");

		location_curveOrigin = ShaderProgram::GetUniformLocation("curveOrigin");
		location_scale = ShaderProgram::GetUniformLocation("scale");
		location_flatMargin = ShaderProgram::GetUniformLocation("flatMargin");
		location_curvature = ShaderProgram::GetUniformLocation("curvature");
	}
};

