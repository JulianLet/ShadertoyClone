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
    vec3 a = vec3(0.7f, 0.f, 0.f);
    vec3 b = vec3(-0.5f, 0.3f, 0.3f);
    vec3 c = vec3(0.8f, 0.8f, 0.8f);
    vec3 d = vec3(0.6f, 0.f, -0.2f);

    return a + b*cos(6.28318*(c*t+d));
}

//returns dot product with itself
float dot2(vec2 v)
{
    return (v.x * v.x + v.y * v.y);
}

//from https://iquilezles.org/articles/distfunctions2d/
float sdHeart( vec2 p )
{
    p.x = abs(p.x);

    if( p.y+p.x>1.0 )
    {
        return sqrt(dot2(p-vec2(0.25,0.75))) - sqrt(2.0)/4.0;
    }
    
        return sqrt(min(dot2(p-vec2(0.00,1.00)),
                dot2(p-0.5*max(p.x+p.y,0.0)))) * sign(p.x-p.y);
}



void main()
{
    vec3 finalColor = vec3(0.0f);
    vec2 uv = fragPos + vec2(0, 0.5);

    float d = sdHeart(uv) * exp(-length(fragPos));
    d = -d;
    d = 0.05f / d;

    vec3 col = palette(length(fragPos) + u_Timer * 0.7f);
    finalColor += col * d;

    color = vec4(finalColor, 1.0f); 
};