#shader vertex
#version 330 core

layout (location = 0) in vec4 position;

void main()
{
	gl_Position = position;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform float u_Radius;
uniform float u_InnerCircle;
uniform float u_OuterCircle;
uniform vec2 u_Center;

vec2 fragPos = gl_FragCoord.xy; //get current fragment position

//Convert to normalized device coordinates (NDC)
//vec2 ndcPos = fragPos * 2.0 - 1.0;

void main()
{
	float dist = distance(fragPos, u_Center);

	if (dist == u_Radius)
	{
		color = vec4(0.0f, 1.0f, 0.0f, 1.0f); //green
	}
	else if (dist <= u_Radius && dist >= u_InnerCircle)
	{
		color = vec4(0.0f, 0.0f, 1.0f, 1.0f); //blue
	}
	else if (dist >= u_Radius && dist <= u_OuterCircle)
	{
		color = vec4(1.0f, 0.0f, 0.0f, 1.0f); //red
	}
	else
	{
		discard;
	}
};