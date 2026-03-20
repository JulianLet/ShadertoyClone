#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;

uniform mat4 u_MVP;
uniform mat4 u_Model;

out vec3 fragNormal;
out vec3 fragPosition;

void main()
{
	gl_Position = u_MVP * position;
	fragNormal = mat3(transpose(inverse(u_Model))) * normal;
	fragPosition = vec3(u_Model * position);
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 fragNormal;
in vec3 fragPosition;

uniform vec4 u_ObjectColor;
uniform vec3 u_CameraPos;
uniform vec3 u_LightPos;
uniform vec4 u_LightColor;

void main()
{
	//ambient light
	float ambientStrenght = 0.3f;
	vec4 ambient = ambientStrenght * u_LightColor;

	//diffuse lighting -> generally reflected into camera area
	vec3 norm = normalize(fragNormal);
	vec3 lightDirection = normalize(u_LightPos - fragPosition);
	float diff = max(dot(norm, lightDirection), 0.0f);
	vec4 diffuse = diff * u_LightColor;

	//specular lighting -> directly reflected into camera so strong effect
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(u_CameraPos - fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32); //raised to power of 32 for stronger effect
	vec4 specular = specularStrength * spec * u_LightColor;

	vec4 light = (ambient + diffuse + specular); 

	color = u_ObjectColor * light;
};