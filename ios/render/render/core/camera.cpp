//
//  camera.cpp
//  lh_render
//
//  Created by liu on 2018/6/25.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "camera.hpp"

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
    Vector3f View(1.0f, 0.0f, 0.0f);
    View.Rotate(_angle_h, Vaxis);
    View.Normalize();
    
    Vector3f Haxis = Vaxis.Cross(View);
    Haxis.Normalize();
    View.Rotate(_angle_v, Haxis);
    
    _target = View;
    _target.Normalize();
    
    _up = _target.Cross(Haxis);
    _up.Normalize();

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
