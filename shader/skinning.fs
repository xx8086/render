#version 300 es
precision highp float;
in vec2 TexCoord0;
//in vec3 Normal0;
//in vec3 WorldPos0;
uniform sampler2D gColorMap;
layout(location = 0) out vec4 FragColor;

void main(){
    FragColor = texture(gColorMap, TexCoord0.xy) ;
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
