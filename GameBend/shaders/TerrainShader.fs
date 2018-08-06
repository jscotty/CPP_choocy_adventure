#version 400 core

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
in float visibility;

out vec4 out_Color;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;
uniform vec3 attenuation;

uniform vec3 lightColor;

uniform float shininess;
uniform float reflectivity;
uniform vec3 skyColor;

const float diffuseFactor = 0.5;

void main(){
	vec2 invertedTexCoord; invertedTexCoord.x = pass_textureCoords.x; invertedTexCoord.y = 1.0 - pass_textureCoords.y;

	vec4 blendMapColor = texture(blendMap, pass_textureCoords);

	float backTextrureAmount = 1-(blendMapColor.r + blendMapColor.g + blendMapColor.b);
	vec2 tiledCoords = invertedTexCoord * 80.0;

	vec4 backgroundTextureColor = texture(backgroundTexture, tiledCoords) * backTextrureAmount;
	vec4 rTextureColor = texture(rTexture, tiledCoords) * blendMapColor.r;
	vec4 gTextureColor = texture(gTexture, tiledCoords) * blendMapColor.g;
	vec4 bTextureColor = texture(bTexture, tiledCoords) * blendMapColor.b;

	vec4 totalColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;
	
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);
	vec3 unitCameraVector = normalize(toCameraVector);
	float distance = length(toLightVector);
	float attenuationFactor = attenuation.x + (attenuation.y * distance) + (attenuation.z * distance * distance);

	float nDotl = dot(unitNormal, unitLightVector);
	float brightness = max(nDotl, 0.1);
	vec3 diffuse = (brightness * lightColor) / attenuationFactor;

	vec3 lightDirection = -unitCameraVector;
	vec3 relflectedLightDirection = reflect(lightDirection,unitNormal);

	float specularFactor = dot(relflectedLightDirection, unitCameraVector);
	specularFactor = max(specularFactor,0.2);
	float dampedFactor = pow(specularFactor, shininess);
	vec3 specular = dampedFactor * lightColor;

	out_Color = vec4(diffuse,1.0) * totalColor;
	out_Color = mix(vec4(skyColor, 1.0), out_Color, visibility);
}