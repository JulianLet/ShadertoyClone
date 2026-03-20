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
uniform vec2 u_Center;

vec2 fragPos = gl_FragCoord.xy; //get current fragment position

//Convert to normalized device coordinates (NDC)
//vec2 ndcPos = fragPos * 2.0 - 1.0;

void main()
{
	if (distance(fragPos, u_Center) <= u_Radius)
	{
		color = vec4(0.0, 0.0, 1.0, 1.0);
	}
	else
	{
		discard;
	}
};