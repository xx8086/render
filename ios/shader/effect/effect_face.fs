#version 300 es
precision mediump float;
in vec3 our_color;
in vec2 texture_coord;
uniform float ratio;
uniform sampler2D imput_image_texture;
layout(location = 0) out vec4 o_FragColor;
bool equal_float(float a, float b){
    if(a > b && a < b + 0.001){
        return true;
    }
    return false;
}
void main()
{
    /*
    vec2 center = vec2(0.5, 0.5);
    vec2 distance = center - texture_coord;
    float x = center.x + center.x*(-distance.x/center.x) * ratio;
    float y = center.y + center.y*(-distance.y/center.y) * ratio;
    vec2 tex = vec2(x,y);
    o_FragColor = texture(imput_image_texture, tex);
     */
    
    o_FragColor = texture(imput_image_texture, texture_coord);
    /*
    if (((texture_coord.x > 0.370f && texture_coord.x < 0.371f) ||
         (texture_coord.x > 0.449f && texture_coord.x < 0.45f))&&
        texture_coord.y > 0.38 && texture_coord.y < 0.402){
        o_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
     */
    if ((equal_float(texture_coord.x, 0.370f) ||
         equal_float(texture_coord.x, 0.447f)) &&
        texture_coord.y > 0.383 && texture_coord.y < 0.404){
        o_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else if(texture_coord.x > 0.370 && texture_coord.x < 0.447){
        
        if (equal_float(texture_coord.y, 0.392f)){
            o_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
        }
        else if(equal_float(texture_coord.y, 0.383f) ||
                equal_float(texture_coord.y, 0.404f)){
            o_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        }

        if (texture_coord.y > 0.383f && texture_coord.y < 0.392f){
            vec2 tex = vec2(texture_coord.x, texture_coord.y - ratio * 0.005f);
            o_FragColor = texture(imput_image_texture, tex);
        }
        else if (texture_coord.y > 0.392f && texture_coord.y < 0.404f){
            vec2 tex = vec2(texture_coord.x, texture_coord.y + ratio * 0.005f);
            o_FragColor = texture(imput_image_texture, tex);
        }
        
    }
}

