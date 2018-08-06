#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H


#include "ShaderProgram.h"
#include <string>
#include <iostream>
#include <gl\glew.h>
#include "Light.h"

class TerrainShader : public ShaderProgram {
private:
	GLuint location_tranformMatrix;
	GLuint location_viewMatrix;
	//GLuint location_projectionMatrix;
	GLuint location_lightPosition;
	GLuint location_lightColor;
	GLuint location_shininess;
	GLuint location_reflectivity;
	GLuint location_skyColor;
	GLuint location_backgroundTexture;
	GLuint location_rTexture;
	GLuint location_gTexture;
	GLuint location_bTexture;
	GLuint location_blendMap;
	GLuint location_attenuation;

	GLuint location_curveOrigin;
	GLuint location_scale;
	GLuint location_flatMargin;
	GLuint location_curvature;

public:
	TerrainShader() : ShaderProgram("./shaders/TerrainShader") { }
	~TerrainShader() {}
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
	void LoadSkyColor(glm::vec3 skyColor) {
		ShaderProgram::LoadVector3(location_skyColor, skyColor);
	}
	void ConnectTextureUnits() {
		ShaderProgram::LoadInteger(location_backgroundTexture, 0);
		ShaderProgram::LoadInteger(location_rTexture, 1);
		ShaderProgram::LoadInteger(location_gTexture, 2);
		ShaderProgram::LoadInteger(location_bTexture, 3);
		ShaderProgram::LoadInteger(location_blendMap, 4);
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
		location_skyColor = ShaderProgram::GetUniformLocation("skyColor");
		location_backgroundTexture = ShaderProgram::GetUniformLocation("backgroundTexture");
		location_rTexture = ShaderProgram::GetUniformLocation("gTexture");
		location_gTexture = ShaderProgram::GetUniformLocation("gTexture");
		location_bTexture = ShaderProgram::GetUniformLocation("bTexture");
		location_blendMap = ShaderProgram::GetUniformLocation("blendMap");
		location_attenuation = ShaderProgram::GetUniformLocation("attenuation");

		location_curveOrigin = ShaderProgram::GetUniformLocation("curveOrigin");
		location_scale = ShaderProgram::GetUniformLocation("scale");
		location_flatMargin = ShaderProgram::GetUniformLocation("flatMargin");
		location_curvature = ShaderProgram::GetUniformLocation("curvature");
	}
};


#endif // !TERRAINSHADER_H