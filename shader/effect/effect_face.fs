#version 300 es
precision highp float;
in vec3 our_color;
in vec2 texture_coord;
uniform float screen_width;
uniform float scrreen_hight;
uniform float ratio;
uniform sampler2D imput_image_texture;

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
    if(a > b && a < b + 0.001){
        return true;
    }
    return false;
}

void zui(){
    o_FragColor = texture(imput_image_texture, texture_coord);
    /*
     if (((texture_coord.x > 0.370f && texture_coord.x < 0.371f) ||
     (texture_coord.x > 0.449f && texture_coord.x < 0.45f))&&
     texture_coord.y > 0.38 && texture_coord.y < 0.402){
     o_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
     }
     
     if ((equal_float(texture_coord.x, 0.370f) ||
     equal_float(texture_coord.x, 0.447f)) &&
     texture_coord.y > 0.383 && texture_coord.y < 0.404){
     o_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
     }
     */

    if(texture_coord.x > 0.370 && texture_coord.x < 0.447){
        float top = 0.350f;
        float bottom = 0.430f;
        float middle = 0.391f;
        float dis = ratio * 0.01f;
        if(((texture_coord.y > middle - dis) && (texture_coord.y <= middle)) ||
           ((texture_coord.y >= middle) && (texture_coord.y <= middle + dis))){
            o_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        }
        
        if (texture_coord.y > top && texture_coord.y < middle - dis){
            vec2 tex = vec2(texture_coord.x, texture_coord.y + dis);
            o_FragColor = texture(imput_image_texture, tex);
        }
        else if (texture_coord.y > middle + dis && texture_coord.y < bottom){
            vec2 tex = vec2(texture_coord.x, texture_coord.y  - dis);
            o_FragColor = texture(imput_image_texture, tex);
        }
    }
}
void main()
{
    zui();
    //zoom();
    //o_FragColor = texture(imput_image_texture, texture_coord/2.0);
}

