#version 450 core
out vec4 o_color;

float computeMandelBrot(vec2 c, int maxIteration)
{
    vec2 z = vec2(0, 0);
    for (int i = 0; i < maxIteration; i++)
    {
        //Z^2 + C
        z = vec2(z.x * z.x - z.y * z.y, 2 * z.x * z.y) + c;
        
        if (sqrt(z.x * z.x + z.y * z.y) >= 2)
        {
            return i / maxIteration;
        }
    }
 
    return 1;
}

void main()
{   
    const int width = 1600;
    const int height = 900;
    
    vec2 c =  gl_FragCoord.xy / vec2(width, height);
    float result = computeMandelBrot(c, 1000);

    o_color = vec4(result, 0, 0, 1);
}