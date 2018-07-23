#version 300 es
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoords;
out vec3 our_color;
out vec2 texture_coord;
void main(){
    our_color = aColor;
    texture_coord = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}
