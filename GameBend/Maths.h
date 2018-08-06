#ifndef MATHS_H
#define MATHS_H

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Entity.h"

class Maths {
public:
	static glm::mat4 CreateTransformationMatrix(glm::vec2 translation, glm::vec2 scale) {
		glm::mat4 matrix;

		glm::mat4 posMatrix = glm::translate(glm::vec3(translation.x,translation.y, 0));
		glm::mat4 scaleMatrix = glm::scale(glm::vec3(scale.x, scale.y, 0));

		matrix = posMatrix * scaleMatrix;

		return matrix;
	}
	static glm::mat4 CreateTransformationMatrix(glm::vec3 translation, float rotX, float rotY, float rotZ, glm::vec3 scale) {
		glm::mat4 matrix;

		glm::mat4 posMatrix = glm::translate(translation);
		glm::mat4 rotXMatrix = glm::rotate(rotX, glm::vec3(1.0, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(rotY, glm::vec3(0, 1.0, 0));
		glm::mat4 rotZMatrix = glm::rotate(rotZ, glm::vec3(0, 0, 1.0));
		glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;
		glm::mat4 scaleMatrix = glm::scale(scale);


		matrix = posMatrix * rotMatrix * scaleMatrix;

		return matrix;
	}
	static glm::mat4 CreateTransformationMatrix(Entity entity) {
		glm::mat4 posMatrix = glm::translate(entity.GetPosition());
		glm::mat4 rotXMatrix = glm::rotate(entity.GetRotation().x, glm::vec3(1.0, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(entity.GetRotation().y, glm::vec3(0, 1.0, 0));
		glm::mat4 rotZMatrix = glm::rotate(entity.GetRotation().z, glm::vec3(0, 0, 1.0));
		glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;
		glm::mat4 scaleMatrix = glm::scale(entity.GetScale());

		return posMatrix * rotMatrix * scaleMatrix;
	}
};

#endif // !MATHS_H
