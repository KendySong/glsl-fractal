#version 450 core
precision highp float;

out vec4 o_color;

uniform float u_zoom;
uniform vec2 u_offset;
uniform int u_precision;

uniform vec2 u_windowSize;
uniform int u_fractalType;

uniform vec2 u_animation;
uniform vec3 u_colorIn;
uniform vec3 u_colorOut;

vec4 computeMandelBrot(vec2 c, int maxIteration)
{
    vec2 z = vec2(0, 0);
    for (int i = 0; i < maxIteration; i++)
    {
        //Z^2 + C
        z = vec2(z.x * z.x - z.y * z.y, 2 * z.x * z.y) + c;
        
        if (sqrt(z.x * z.x + z.y * z.y) >= 2)
        {
            float intensity = float(i) / maxIteration;
            return vec4(u_colorOut, 1) * intensity;
        }
    }
 
    return vec4(u_colorIn, 1);
}

vec4 computeJulia(vec2 c, int maxIteration)
{
    vec2 z = c;
    for (int i = 0; i < maxIteration; i++)
    {
        //Z = C
        //Z^2 + animation
        z = vec2(z.x * z.x - z.y * z.y, 2 * z.x * z.y) + u_animation;
        if (sqrt(z.x * z.x + z.y * z.y) >= 2)
        {
            float intensity = float(i) / maxIteration;
            return vec4(u_colorOut, 1) * intensity;
        }
    }
 
    return vec4(u_colorIn, 1);
}

vec4 computeBurningShip(vec2 c, int maxIteration)
{
    vec2 z = c;
    for (int i = 0; i < maxIteration; i++)
    {
        //Z = abs(Z)
        //Z^2 + C
        z = abs(z);
        z = vec2(z.x * z.x - z.y * z.y, 2 * z.x * z.y) + c - 0.2;
        if (sqrt(z.x * z.x + z.y * z.y) >= 2)
        {
            float intensity = float(i) / maxIteration;
            return vec4(u_colorOut, 1) * intensity;
        }
    }
 
    return vec4(u_colorIn, 1);
}

void main()
{       
    vec2 c = u_zoom * (gl_FragCoord.xy - 0.5 * u_windowSize) / u_windowSize.x;
    c += u_offset;

    switch(u_fractalType)
    {
        case 0 : 
            o_color = computeMandelBrot(c, u_precision);
            break;

        case 1 : 
            o_color = computeJulia(c, u_precision);
            break;

        case 2 :
            o_color = computeBurningShip(c, u_precision);
            break;

        default : 
            o_color = vec4(0, 0, 0, 0);
            break;
    }
}