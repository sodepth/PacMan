#version 120

uniform sampler2D texture;
uniform float time;
uniform float uStrength = .9;
uniform float uBrightness = 2;

void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    vec4 base = texture2D(texture, uv);
    
    float x = uv.x * 5.0 + time;
    vec3 rainbow = 0.5 + 0.5 * cos(vec3(x + 0.0, x + 2.0, x + 4.0));

    vec3 col = mix(base.rgb, base.rgb * rainbow, uStrength);

    col *= uBrightness;

    gl_FragColor = vec4(col, base.a);
}
