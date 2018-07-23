#version 300 es
layout(location = 0) in vec3 vertex;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
void main(){
   gl_Position = proj * view * model * vec4(vertex.x, vertex.y, vertex.z, 1.0);;
}

