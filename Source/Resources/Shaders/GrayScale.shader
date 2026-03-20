#shader vertex
#version 330 core
        
layout(location = 0) in vec4 position;

out vec2 fragPos;
        
void main()
{
    fragPos = position.xy;
    gl_Position = position; 
};



#shader fragment
#version 330 core
        
layout(location = 0) out vec4 color;

in vec2 fragPos;

uniform vec4 u_Color;
uniform float u_GrayScale;
uniform float u_Timer;

vec4 lerp(vec4 colorone, vec4 colortwo, float value)
{
	return (colorone + value*(colortwo-colorone));
}

void main()
{
    float grayScaleFactor = 0.299 * u_Color.x + 0.587f * u_Color.y + 0.114f * u_Color.z;
    vec4 grayColor = vec4(grayScaleFactor, grayScaleFactor, grayScaleFactor, 1.0f);

    color = mix(u_Color, grayColor, u_GrayScale);
};