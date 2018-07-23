//
//  pipeline.cpp
//  megranate
//
//  Created by liu on 2018/7/12.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "pipeline.hpp"
#include "../math/math_common.hpp"
#include "../object/config_render.h"

namespace megranate {
    
    void Pipeline::init_persproj_transform(Mat4f& m4f, const PersProjInfo& p)
    {
        const float ar         = p.Width / p.Height;
        const float zRange     = p.zNear - p.zFar;
        const float tanHalfFOV = tanf(ToRadian(p.FOV / 2.0f));
        
        m4f.m[0][0] = 1.0f/(tanHalfFOV * ar); m4f.m[0][1] = 0.0f;            m4f.m[0][2] = 0.0f;            m4f.m[0][3] = 0.0;
        m4f.m[1][0] = 0.0f;                   m4f.m[1][1] = 1.0f/tanHalfFOV; m4f.m[1][2] = 0.0f;            m4f.m[1][3] = 0.0;
        m4f.m[2][0] = 0.0f;                   m4f.m[2][1] = 0.0f;            m4f.m[2][2] = (-p.zNear - p.zFar)/zRange ; m4f.m[2][3] = 2.0f*p.zFar*p.zNear/zRange;
        m4f.m[3][0] = 0.0f;                   m4f.m[3][1] = 0.0f;            m4f.m[3][2] = 1.0f;            m4f.m[3][3] = 0.0;
    }
    
    mg_void Pipeline::set_wvp_trans(){
        get_world_trans();
        get_view_trans();
        get_proj_trans();
        _wvp_transformation = _w_transformation * _v_transformation * _proj_transformation;
    }
    mg_void Pipeline::set_pvw_trans(){
        get_world_trans();
        get_view_trans();
        get_proj_trans();
        _pvw_transformation = _proj_transformation * _v_transformation * _w_transformation;
    }
    mg_void Pipeline::set_world_trans(){
        Mat4f ScaleTrans, RotateTrans, TranslationTrans;
        init_mat_scale(ScaleTrans, _scale.x, _scale.y, _scale.z);
        init_rotate_transform(RotateTrans, _rotate_info.x, _rotate_info.y, _rotate_info.z);
        init_mat_translation(TranslationTrans, _world_pos.x, _world_pos.y, _world_pos.z);
        _w_transformation = TranslationTrans * RotateTrans * ScaleTrans;
    }
    mg_void Pipeline::set_view_trans(){
        Mat4f CameraTranslationTrans, CameraRotateTrans;
        init_mat_translation(CameraTranslationTrans, -_camera.pos.x, -_camera.pos.y, -_camera.pos.z);
        init_camera_transform(CameraRotateTrans, _camera.target, _camera.up);
        _v_transformation = CameraRotateTrans * CameraTranslationTrans;
    }
    mg_void Pipeline::set_proj_trans(){
        init_persproj_transform(_proj_transformation, _pers_proj_info);
    }
    const Mat4f& Pipeline::get_proj_trans(){
        return _proj_transformation;
    }
    
    const Mat4f& Pipeline::get_world_trans(){
        return _w_transformation;
    }
    
    const Mat4f& Pipeline::get_view_trans(){
        return _v_transformation;
    }
    
    const Mat4f& Pipeline::get_wvp_trans(){
        return _wvp_transformation;
    }
    
    const Mat4f& Pipeline::get_pvw_trans(){
        return _pvw_transformation;
    }
}
