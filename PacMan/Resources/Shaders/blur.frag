#version 120

uniform sampler2D texture;
uniform vec2 resolution;
uniform float radius;

const float pi = 3.1415926535897932384626433832795;

void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    vec2 texel = 1.0 / resolution;
    
    int size = int(radius);
    float sigma = radius / 2.0;
    float twoSigma2 = 2.0 * sigma * sigma;

    vec4 sum = vec4(0.0);
    float weightSum = 0.0;
    
    for (int x = -size; x <= size; ++x) {
        for (int y = -size; y <= size; ++y) {
            float dist2 = float(x * x + y * y);
            float w = exp(-dist2 / twoSigma2) / (pi * twoSigma2);
            vec2 offset = vec2(float(x), float(y)) * texel;
            sum += texture2D(texture, uv + offset) * w;
            weightSum += w;
        }
    }

    gl_FragColor = sum / weightSum;
}