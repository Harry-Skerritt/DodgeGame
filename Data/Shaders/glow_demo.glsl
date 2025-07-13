#version 120

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord/iResolution.xy;

    vec2 rpos = uv - 0.5;
    rpos.y /= iResolution.x/iResolution.y;


    float distance = length(rpos);

    float scale = 0.1;
    float fade = 2.5;
    float strength = pow(1.0 / distance * scale, fade);

    vec3 color = strength * vec3(0.8, 0.5, 0.0);

    color = 1.0 - exp( -color );

    fragColor = vec4(color, 0.9);
}
