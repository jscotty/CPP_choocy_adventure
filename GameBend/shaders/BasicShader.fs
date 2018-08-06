#version 400 core

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
in float visibility;

out vec4 out_Color;

uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform vec3 attenuation;
uniform float shininess;
uniform float reflectivity;
uniform vec3 skyColor;

void main(){
	
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);
	vec3 unitCameraVector = normalize(toCameraVector);
	float distance = length(toLightVector);
	float attenuationFactor = attenuation.x + (attenuation.y * distance) + (attenuation.z * distance * distance);

	float nDotl = dot(unitNormal, unitLightVector);
	float brightness = max(nDotl, 0.5);
	vec3 diffuse = (brightness * lightColor)/attenuationFactor;

	vec3 lightDirection = -unitCameraVector;
	vec3 relflectedLightDirection = reflect(lightDirection,unitNormal);

	float specularFactor = dot(relflectedLightDirection, unitCameraVector);
	specularFactor = max(specularFactor,0.2);
	float dampedFactor = pow(specularFactor, shininess);
	vec3 specular = dampedFactor * lightColor;

	vec4 texture = texture(textureSampler, pass_textureCoords);
	if(texture.a < 0.5){
		discard;
	}

	out_Color = vec4(diffuse,1.0) * texture + vec4(specular, 1.0);
	out_Color = mix(vec4(skyColor, 1.0), out_Color, visibility);
}