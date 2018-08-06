#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <string>


class ShaderProgram{
public:

	ShaderProgram(const std::string& fileName);

	void Bind();
	void Unbind();

	~ShaderProgram();
	void Link();
protected:
	virtual void GetAllUniforms() = 0;
	void BindAttribute(int attribute, const GLchar* variableName);
	GLuint GetUniformLocation(GLchar* uniformName);

	void LoadFloat(GLuint location, float value) {
		glUniform1f(location, value);
	}
	void LoadDouble(GLuint location, double value) {
		glUniform1d(location, value);
	}
	void LoadInteger(GLuint location, int value) {
		glUniform1i(location, value);
	}
	void LoadVector4(GLuint location, glm::vec4 value) {
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	void LoadVector3(GLuint location, glm::vec3 value) {
		glUniform3f(location, value.x, value.y, value.z);
	}
	void LoadVector2(GLuint location, glm::vec2 value) {
		glUniform2f(location, value.x, value.y);
	}
	void LoadMatrix4(GLuint location, glm::mat4 value) {
		glUniformMatrix4fv(location, 1 , GL_FALSE, &value[0][0]);
	}
	void LoadBoolean(GLuint location, bool value) {
		float loadValue = 0;
		if (value) loadValue = 1;
		glUniform1f(location, loadValue);
	}

private:
	static const unsigned int NUM_SHADERS = 2;

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};

#endif // !SHADERPROGRAM_H