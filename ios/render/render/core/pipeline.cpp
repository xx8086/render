//
//  pipeline.cpp
//  render
//
//  Created by liu on 2018/6/28.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "pipeline.hpp"


const Mat4f& Pipeline::get_proj_trans(){
    _proj_transformation.InitPersProjTransform(_pers_proj_info);
    return _proj_transformation;
}

const Mat4f& Pipeline::get_world_trans(){
    Mat4f ScaleTrans, RotateTrans, TranslationTrans;
    ScaleTrans.InitScaleTransform(_scale.x, _scale.y, _scale.z);
    RotateTrans.InitRotateTransform(_rotate_info.x, _rotate_info.y, _rotate_info.z);
    TranslationTrans.InitTranslationTransform(_world_pos.x, _world_pos.y, _world_pos.z);
    
    _w_transformation = TranslationTrans * RotateTrans * ScaleTrans;
    return _w_transformation;
}

const Mat4f& Pipeline::get_view_trans(){
    Mat4f CameraTranslationTrans, CameraRotateTrans;
    CameraTranslationTrans.InitTranslationTransform(-_camera.pos.x, -_camera.pos.y, -_camera.pos.z);
    CameraRotateTrans.InitCameraTransform(_camera.target, _camera.up);
    _v_transformation = CameraRotateTrans * CameraTranslationTrans;
    
    return _v_transformation;
}

const Matrix4f& Pipeline::get_wvp_trans(){
    get_world_trans();
    get_view_trans();
    get_proj_trans();
    _wvp_transformation = _w_transformation * _v_transformation * _proj_transformation;
    return _wvp_transformation;
}

const Mat4f& Pipeline::get_pvw_trans(){
    get_world_trans();
    get_view_trans();
    get_proj_trans();
    _pvw_transformation = _proj_transformation * _v_transformation * _w_transformation;
    return _pvw_transformation;
}
