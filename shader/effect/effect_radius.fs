#version 300 es
precision mediump float;
in vec3 our_color;
in vec2 texture_coord;
uniform float ratio;
uniform sampler2D imput_image_texture;
const float angle = 90.0;
const float uR = 0.5;
layout(location = 0) out vec4 o_FragColor;

void main(){
    ivec2 ires = ivec2(240, 320);
    float res = float(ires.s);
    float radius = res * uR * ratio;
    vec2 st = texture_coord;
    vec2 xy = res * st;
    vec2 dxy = xy - vec2(res/2., res/2.);
    float r = length(dxy);
    if(r <= radius){
        //抛物线递减因子：(1.0-(r/Radius)*(r/Radius) )
        float beta = atan(dxy.y, dxy.x) + radians(angle) * 2.0 * (1.0 - (r/radius) * (r/radius));//(1.0 - r/Radius);
        xy = res/2. + r * vec2(cos(beta), sin(beta));
    }
    st = xy/res;
    o_FragColor = texture(imput_image_texture, st);

}
