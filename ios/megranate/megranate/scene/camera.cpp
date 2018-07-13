//
//  camera.cpp
//  megranate
//
//  Created by liu on 2018/7/12.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "../object/config_render.h"
#include "../math/math_common.hpp"
#include "camera.hpp"

namespace megranate {
    
    void rotate(Vec3f& me, float Angle, const Vec3f& Axe){
        const float SinHalfAngle = sinf(ToRadian(Angle/2));
        const float CosHalfAngle = cosf(ToRadian(Angle/2));
        
        const float Rx = Axe.x * SinHalfAngle;
        const float Ry = Axe.y * SinHalfAngle;
        const float Rz = Axe.z * SinHalfAngle;
        const float Rw = CosHalfAngle;
        Quaternion RotationQ(Rx, Ry, Rz, Rw);
        Quaternion ConjugateQ = RotationQ.conjugate();
        Quaternion W = RotationQ * (me) * ConjugateQ;
        
        me.x = W.x;
        me.y = W.y;
        me.z = W.z;
    }
    
    Camera::Camera(Vec3f position, Vec3f target, Vec3f up) : _position(position), _target(target), _up(up){
        update_camera_vectors();
    };
    
    void Camera::resize(float w, float h){
        _width = w;
        _height = h;
    }
    
    const PersProjInfo& Camera::get_proj_info()const{
        return _proj_info;
    };
    
    void Camera::set_proj_info(PersProjInfo proj){
        _proj_info = proj;
    };
    
    void Camera::update_camera_vectors(){
        const Vec3f Vaxis(0.0f, 1.0f, 0.0f);
        Vec3f View(1.0f, 0.0f, 0.0f);
        rotate(View, _angle_h, Vaxis);
        View.normalize();
        
        Vec3f Haxis = cross(Vaxis, View);
        Haxis.normalize();
        rotate(View, _angle_v, Haxis);
        
        _target = View;
        _target.normalize();
        
        _up = cross(_target, Haxis);
        _up.normalize();
        
    }
    
    const Vec3f& Camera::get_postion(){
        return _position;
    }
    const Vec3f& Camera::get_up(){
        return _up;
    }
    const Vec3f& Camera::get_target(){
        return _target;
    }
    
    Quaternion::Quaternion(float _x, float _y, float _z, float _w){
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }
    
    void Quaternion::normalize(){
        float Length = sqrtf(x * x + y * y + z * z + w * w);
        
        x /= Length;
        y /= Length;
        z /= Length;
        w /= Length;
    }
    
    
    Quaternion Quaternion::conjugate(){
        Quaternion ret(-x, -y, -z, w);
        return ret;
    }
    
    
    Vec3f Quaternion::to_degrees(){
        float f[3];
        f[0] = atan2(x * z + y * w, x * w - y * z);
        f[1] = acos(-x * x - y * y - z * z - w * w);
        f[2] = atan2(x * z - y * w, x * w + y * z);
        f[0] = ToDegree(f[0]);
        f[1] = ToDegree(f[1]);
        f[2] = ToDegree(f[2]);
        
        return Vec3f(f[0], f[1], f[2]);
    }
    
    
    Quaternion operator*(const Quaternion& l, const Quaternion& r){
        const float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
        const float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
        const float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
        const float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

        Quaternion ret(x, y, z, w);
        return ret;
    }
    
    Quaternion operator*(const Quaternion& q, const Vec3f& v){
        const float w = - (q.x * v.x) - (q.y * v.y) - (q.z * v.z);
        const float x =   (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
        const float y =   (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
        const float z =   (q.w * v.z) + (q.x * v.y) - (q.y * v.x);
        
        Quaternion ret(x, y, z, w);
        return ret;
    }


}
