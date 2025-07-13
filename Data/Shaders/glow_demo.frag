#version 120

uniform vec2 iResolution;
uniform vec4 glowColor;
uniform float glowSize;

void main()
{
    vec2 uv = gl_FragCoord.xy / iResolution;

    vec2 rpos = uv - 0.5;
    rpos.y /= iResolution.x / iResolution.y;

    float distance = length(rpos);
    float scale = 0.1;

    float strength = pow(1.0 / distance * scale, glowSize);

    vec3 color = vec3(glowColor.r, glowColor.g, glowColor.b);

    color *= strength;
    color = 1.0 - exp( -color );

    gl_FragColor = vec4(color, 1.0);
}
