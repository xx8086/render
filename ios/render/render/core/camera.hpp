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
#include "matrix_transform.hpp"
#include <vector>
#include <OpenGLES/ES3/gl.h>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW        = -90.0f;
const float PITCH      =  0.0f;
const float SPEED      =  2.5f;
const float SENSITIVTY =  0.1f;
const float ZOOM       =  45.0f;

class Camera
{
public:
    Camera(Vec3f position = Vec3f(0.0f, 0.0f, 0.0f), Vec3f up = Vec3f(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    
    Mat4f get_view_matrix();
    Mat4f get_projection();
    
    void resize(float w, float h, float near, float far);
    void process_key_board(Camera_Movement direction, float deltaTime);
    void process_mouse_movement(float xoffset, float yoffset, bool constrainPitch = true);
    void process_mouse_scroll(float yoffset);
private:
    // Calculates the front vector from the Camera's (updated) Eular Angles
    void update_camera_vectors();
private:
    Vec3f _position;
    Vec3f _front;
    Vec3f _up;
    Vec3f _right;
    Vec3f _world_up;
    float _yaw;
    float _pitch;
    float _movement_seed;
    float _mouse_sensitivity;
    float _zoom;
    
    float _width;
    float _height;
    float _near;
    float _far;
};
#endif /* camera_h */
