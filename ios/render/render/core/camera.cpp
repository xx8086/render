//
//  camera.cpp
//  lh_render
//
//  Created by liu on 2018/6/25.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "camera.hpp"
#include "glm.hpp"

Camera::Camera(Vec3f position, Vec3f up, float yaw, float pitch) :
_front(Vec3f(0.0f, 0.0f, -1.0f)), _movement_seed(SPEED), _mouse_sensitivity(SENSITIVTY), _zoom(ZOOM){
    _position = position;
    _world_up = up;
    _yaw = yaw;
    _pitch = pitch;
    update_camera_vectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
_front(Vec3f(0.0f, 0.0f, -1.0f)), _movement_seed(SPEED), _mouse_sensitivity(SENSITIVTY), _zoom(ZOOM){
    _position = Vec3f(posX, posY, posZ);
    _world_up = Vec3f(upX, upY, upZ);
    _yaw = yaw;
    _pitch = pitch;
    update_camera_vectors();
}

void Camera::resize(float w, float h, float near, float far){
    _width = w;
    _height = h;
    _near = near;
    _far = far;
}

Mat4f Camera::get_projection(){
    return Mat4f(glm::perspective(glm::radians(_zoom), _width/_height, _near, _far));
}

Mat4f Camera::get_view_matrix(){
    glm::vec3 pos(_position.x, _position.y, _position.z);
    glm::vec3 front(_front.x, _front.y, _front.z);
    glm::vec3 up(_up.x, _up.y, _up.z);
    return Mat4f(glm::lookAt(pos, pos + front, up));
}

void Camera::process_key_board(Camera_Movement direction, float deltaTime){
    float velocity = _movement_seed * deltaTime;
    if (direction == FORWARD) _position += _front * velocity;
    if (direction == BACKWARD) _position -= _front * velocity;
    if (direction == LEFT) _position -= _right * velocity;
    if (direction == RIGHT) _position += _right * velocity;
}

void Camera::process_mouse_movement(float xoffset, float yoffset, bool constrainPitch){
    xoffset *= _mouse_sensitivity;
    yoffset *= _mouse_sensitivity;
    
    _yaw   += xoffset;
    _pitch += yoffset;
    if (constrainPitch){
        if (_pitch > 89.0f) _pitch = 89.0f;
        if (_pitch < -89.0f) _pitch = -89.0f;
    }
    update_camera_vectors();
}

void Camera::process_mouse_scroll(float yoffset){
    if (_zoom >= 1.0f && _zoom <= 45.0f) _zoom -= yoffset;
    if (_zoom <= 1.0f) _zoom = 1.0f;
    if (_zoom >= 45.0f) _zoom = 45.0f;
}

void Camera::update_camera_vectors(){
    Vec3f front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    //_front = glm::normalize(front);
    //_right = glm::normalize(glm::cross(_front, _world_up));
    //_up    = glm::normalize(glm::cross(_right,_front));
    _front.Normalize();
    _right = front;
    _right.Cross(_world_up);
    _right.Normalize();
    _up = _right;
    _up.Cross(_front);
    _up.Normalize();

}
