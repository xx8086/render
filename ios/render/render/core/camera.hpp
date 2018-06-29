//
//  camera.hpp
//  lh_render
//
//  Created by liu on 2018/6/25.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include "type_render.h"
#include <vector>
#include <OpenGLES/ES3/gl.h>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera(Vec3f position = Vec3f(0.0f, 0.0f, 0.0f),
           Vec3f target = Vec3f(0.0f, 0.0f, 1.0f),
           Vec3f up = Vec3f(0.0f, 1.0f, 0.0f));
    
    const Vec3f& get_postion();
    const Vec3f& get_up();
    const Vec3f& get_target();
    const PersProjInfo& get_proj_info()const;
    void set_proj_info(PersProjInfo proj);
    void resize(float w, float h);
    void process_key_board(Camera_Movement direction, float deltaTime);
private:
    void update_camera_vectors();
private:
    Vec3f _position;
    Vec3f _target;
    Vec3f _up;
    float _angle_h = 0;
    float _angle_v = 0;
    float _width;
    float _height;
    PersProjInfo _proj_info;
};
#endif /* camera_h */
