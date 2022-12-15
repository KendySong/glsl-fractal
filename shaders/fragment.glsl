#version 450 core
out vec4 o_color;
uniform vec2 u_windowSize;
uniform int u_precision;

vec4 computeMandelBrot(vec2 c, int maxIteration)
{
    vec2 z = vec2(0, 0);
    for (int i = 0; i < maxIteration; i++)
    {
        //Z^2 + C
        z = vec2(z.x * z.x - z.y * z.y, 2 * z.x * z.y) + c;
        
        if (sqrt(z.x * z.x + z.y * z.y) >= 2)
        {
            float light = float(i) / maxIteration;
            return vec4(0, light, 0, 1);
        }
    }
 
    return vec4(0, 0, 0, 1);
}

void main()
{       
    vec2 c = 4 * (gl_FragCoord.xy - 0.5 * u_windowSize) / u_windowSize.x;
    c.x -= 0.25;

    o_color = computeMandelBrot(c, u_precision);
}