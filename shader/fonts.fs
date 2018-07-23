#version 300 es
precision highp float;
uniform vec3 textColor;
layout(location = 0) out vec4 o_FragColor;
void main(){
    o_FragColor = vec4(textColor, 1.0);;
}
