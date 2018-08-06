#version 400 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;
out float visibility;

uniform mat4 transformMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

uniform vec3 curveOrigin;
uniform vec3 scale;
uniform float flatMargin;
uniform float curvature;

const float density = 0.01;
const float gradient = 10;

vec4 Bend(){
	vec4 wpos = transformMatrix * vec4(position, 1.0);

	vec2 xzDistance = (wpos.xz - curveOrigin.xz) / scale.xz; // x and z distance divided by scale for flatting the x or z scale
	float dist = length(xzDistance);

	dist = max(0, dist - flatMargin);

	wpos.y -= dist * dist * curvature; // calculate y curve

	wpos = transformMatrix * wpos; // convert back to object space

	return wpos;
}

void main(){
	vec4 worldPosition = Bend();
	vec4 positionRelativeToCamera = viewMatrix * worldPosition;
	gl_Position = positionRelativeToCamera;
	pass_textureCoords = vec2(textureCoords.x, -textureCoords.y);

	surfaceNormal = (transformMatrix * vec4(normal,0.0)).xyz;
	toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = (inverse(viewMatrix) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;
	
	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance*density), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
}