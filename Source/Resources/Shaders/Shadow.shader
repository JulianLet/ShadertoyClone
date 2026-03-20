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

uniform vec3 u_LightDirection;
uniform vec4 u_LightColor;
uniform mat4 u_LightMatrix;

uniform sampler2D u_DepthMap;

void main()
{
	//ambient light
	float ambientStrenght = 0.2f;
	vec4 ambient = ambientStrenght * u_LightColor;

	//diffuse lighting -> generally reflected into camera area
	vec3 norm = normalize(fragNormal);
	vec3 lightDirection = normalize(-u_LightDirection);
	float diff = max(dot(norm, lightDirection), 0.0f);
	vec4 diffuse = diff * u_LightColor;

	//specular lighting -> directly reflected into camera so strong effect
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(u_CameraPos - fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);
	vec4 specular = specularStrength * spec * u_LightColor;

	//Shadow Calculation
	float shadow = 0.0f;

	//transform to light space
	vec4 fragPosLight = u_LightMatrix * vec4(fragPosition, 1.0f);
	normalize(fragPosLight);//.xyz /= fragPosLight.w; //normalize
	fragPosLight.xyz = fragPosLight.xyz * 0.5f + 0.5f; // map to [0,1] 

	float currentDepth = fragPosLight.z;
	float tolerance = 0.00005; //to prevent jitter
	float closestDepth = texture(u_DepthMap, fragPosLight.xy).r;


	if (currentDepth > closestDepth + tolerance)
	{
		shadow = 1.0f;
	}

	vec4 light = (ambient + diffuse + specular) * (1.0f - shadow * 0.7f); 

	color = u_ObjectColor * vec4(light.xyz, 1.0f);
};