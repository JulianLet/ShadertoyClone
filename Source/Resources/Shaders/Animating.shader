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
uniform float u_Timer;

vec3 palette (float t)
{
    vec3 a = vec3(0.5f, 0.5f, 0.5f);
    vec3 b = vec3(0.5f, 0.5f, 0.5f);
    vec3 c = vec3(1.0f, 1.0f, 1.0f);
    vec3 d = vec3(0.263f, 0.416f, 0.557f);

    return a + b*cos(6.28318*(c*t+d));
}

void main()
{
    vec3 finalColor = vec3(0.0f);
    vec2 uv = fragPos;

    for (int i = 0; i < 4; i++)
    {
        uv = fract(uv * 1.5f) - 0.5f;

        float d = length(uv) * exp(-length(fragPos));
        d = sin(d * 8.f + u_Timer)/ 8.f;
        d = abs(d);
        d = pow(0.01f / d, 1.2f);

        vec3 col = palette(length(fragPos) + i * 0.4f + u_Timer * 0.4f);
        finalColor += col * d;
    }

    color = vec4(finalColor, 1.0f); 
};