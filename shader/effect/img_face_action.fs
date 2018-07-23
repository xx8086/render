#version 300 es
precision highp float;
in vec3 our_color;
in vec2 texture_coord;
uniform float screen_width;
uniform float scrreen_hight;
uniform float ratio;
uniform sampler2D imput_image_texture;
uniform sampler2D mouth_image_texture;
uniform sampler2D tongue_image_texture;

layout(location = 0) out vec4 o_FragColor;
float getdistance(vec2 pos_src, vec2 pos_dist){
    float quadratic_sum = pow((pos_src.x - pos_dist.x), 2.) + pow((pos_src.y - pos_dist.y), 2.);
    return sqrt(quadratic_sum);
}

void zoom(){
    if (getdistance(vec2(0.40, 0.39), texture_coord) > 0.1)
        o_FragColor = texture(imput_image_texture, texture_coord);
    else{
        o_FragColor = texture(imput_image_texture, texture_coord / 2.0 + 0.2);
    }
}

bool equal_float(float a, float b){
    if(a > b - 0.001 && a < b + 0.001){
        return true;
    }
    return false;
}

const float mouth_left = 0.370f;
const float mouth_right = 0.447f;
const float tooth_left = 0.380f;
const float tooth_right = 0.437f;
const float mouth_top = 0.350f;
const float mouth_bottom = 0.430f;
const float mouth_middle = 0.391f;

float tooth(float x){
    if (x <= tooth_left || x >= tooth_right){
        return 0.0f;
    }
    
    float k = 3.1415926f / (tooth_right - tooth_left);
    float b = 1.5707963 - k * tooth_right;
    return cos(b + k * x);
}

float mouth(float x){
    if (x <= mouth_left || x >= mouth_right){
        return 0.0f;
    }
    
    float k = 3.1415926f / (mouth_right - mouth_left);
    float b = 1.5707963 - k * mouth_right;
    return cos(b + k * x);
}

void face(){
    o_FragColor = texture(imput_image_texture, texture_coord);
    if (texture_coord.x > mouth_left && texture_coord.x < mouth_right){
        float mouth_dis = mouth(texture_coord.x) * ratio * 0.01f;
        float mouth_top_dis = mouth_dis * 0.5;
        
        float tooth_dis = tooth(texture_coord.x) * ratio * 1.3f * 0.01f;
        float tooth_top_dis = tooth_dis * 0.5;
        
        
        if(
           ((texture_coord.y > mouth_middle - mouth_top_dis) && (texture_coord.y <= mouth_middle)) ||//top
           ((texture_coord.y >= mouth_middle) && (texture_coord.y <= mouth_middle + mouth_dis))){
            
            if (((texture_coord.y > (mouth_middle + tooth_dis)) && (mouth_middle + mouth_dis) > texture_coord.y) ||
               (texture_coord.y > (mouth_middle - mouth_top_dis) &&(mouth_middle - tooth_top_dis > texture_coord.y))){
                if (mouth_dis > 0.002f)o_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
            }
            else {
                o_FragColor = vec4(0.341176, 0.168627, 0.180392, 1.0);
            }
        }
        
        
        
        if (texture_coord.y > mouth_top && texture_coord.y < mouth_middle - mouth_dis){
            vec2 tex = vec2(texture_coord.x, texture_coord.y + mouth_top_dis);
            o_FragColor = texture(imput_image_texture, tex);
        }
        else if (texture_coord.y > mouth_middle + mouth_dis && texture_coord.y < mouth_bottom){
            vec2 tex = vec2(texture_coord.x, texture_coord.y  - mouth_dis);
            o_FragColor = texture(imput_image_texture, tex);
        }
    }
}

void main()
{
    face();
    //zoom();
    //o_FragColor = texture(imput_image_texture, texture_coord/2.0);
}

