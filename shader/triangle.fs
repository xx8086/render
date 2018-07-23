#version 300 es
precision highp float;
in vec2 TexCoords;
uniform sampler2D texture_diffuse1;
layout(location = 0) out vec4 o_FragColor;
void main()
{
    o_FragColor = texture(texture_diffuse1, TexCoords);
}

