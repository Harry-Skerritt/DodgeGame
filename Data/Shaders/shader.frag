#version 120

uniform vec2 iResolution;
uniform vec4 glowColor;
uniform vec4 coreColor;
uniform float glowSize;

void main()
{
    vec2 uv = gl_TexCoord[0].xy * iResolution;

    vec2 shapeMin = vec2(glowSize, glowSize);
    vec2 shapeMax = iResolution - glowSize;

    vec2 dist = max(shapeMin - uv, uv - shapeMax);
    float maxDist = max(dist.x, dist.y);
    float glow = 1.0 - smoothstep(0.0, glowSize, maxDist);


    bool inShape = all(lessThanEqual(shapeMin, uv)) && all(lessThanEqual(uv, shapeMax));

    vec3 color = mix(glow * glowColor.rgb, coreColor.rgb, float(inShape));
    float alpha = max(glow * glowColor.a, coreColor.a * float(inShape));

    gl_FragColor = vec4(color, alpha);
}
