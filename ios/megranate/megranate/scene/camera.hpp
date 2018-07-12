//
//  camera.hpp
//  megranate
//
//  Created by liu on 2018/7/12.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp
#include "type_render.h"

namespace megranate {
    
    struct PersProjInfo{
        float FOV;
        float Width;
        float Height;
        float zNear;
        float zFar;
    };
    
    
    struct OrthoProjInfo{
        float r;        // right
        float l;        // left
        float b;        // bottom
        float t;        // top
        float n;        // z near
        float f;        // z far
    };
    
    struct Quaternion{
        float x, y, z, w;
        
        Quaternion(float _x, float _y, float _z, float _w);
        void normalize();
        Quaternion conjugate();
        Vec3f to_degrees();
    };
    
    Quaternion operator*(const Quaternion& l, const Quaternion& r);
    Quaternion operator*(const Quaternion& q, const Vec3f& v);
    
    enum Camera_Movement {
        EYE_FORWARD,
        EYE_BACKWARD,
        EYE_LEFT,
        EYE_RIGHT
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
    };}

#endif /* camera_hpp */
