//
//  pipeline.hpp
//  render
//
//  Created by liu on 2018/6/28.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef pipeline_hpp
#define pipeline_hpp

#include "type_render.h"
#include "camera.hpp"


struct Orientation{
    Vec3f scale;
    Vec3f rotation;
    Vec3f pos;
    
    Orientation():
    scale(1.0f, 1.0f, 1.0f),
    rotation(0.0f, 0.0f, 0.0f),
    pos(0.0f, 0.0f, 0.0f){}
};


class Pipeline
{
public:
    Pipeline():_scale(1.0f, 1.0f, 1.0f),
    _world_pos(0.0f, 0.0f, 0.0f),
    _rotate_info(0.0f, 0.0f, 0.0f){}
    
    void scale(float s){
        scale(s, s, s);
    }
    
    
    void scale(const Vec3f& s){
        scale(s.x, s.y, s.z);
    }
    
    void scale(float scale_x, float scale_y, float scale_z){
        _scale.x = scale_x;
        _scale.y = scale_y;
        _scale.z = scale_z;
    }
    
    void world_pos(float x, float y, float z){
        _world_pos.x = x;
        _world_pos.y = y;
        _world_pos.z = z;
    }
    
    void world_pos(const Vec3f& pos){
        _world_pos = pos;
    }
    
    void rotate(float rotate_x, float rotate_y, float rotate_z){
        _rotate_info.x = rotate_x;
        _rotate_info.y = rotate_y;
        _rotate_info.z = rotate_z;
    }
    
    void rotate(const Vec3f& r){
        rotate(r.x, r.y, r.z);
    }
    
    void set_perspective_proj(const PersProjInfo& p){
        _pers_proj_info = p;
    }
    
    void set_orthographic_proj(const OrthoProjInfo& p){
        _ortho_proj_info = p;
    }
    
    void set_camera(const Vec3f& pos, const Vec3f& target, const Vec3f& up){
        _camera.pos = pos;
        _camera.target = target;
        _camera.up = up;
    }
    
    void orient(const Orientation& o){
        _scale      = o.scale;
        _world_pos   = o.pos;
        _rotate_info = o.rotation;
    }
    
    const Mat4f& get_wvp_trans();
    const Mat4f& get_pvw_trans();
    const Mat4f& get_world_trans();
    const Mat4f& get_view_trans();
    const Mat4f& get_proj_trans();
    
private:
    Vec3f _scale;
    Vec3f _world_pos;
    Vec3f _rotate_info;
    
    PersProjInfo _pers_proj_info;
    OrthoProjInfo _ortho_proj_info;
    
    struct {
        Vec3f pos;
        Vec3f target;
        Vec3f up;
    } _camera;
    
    Mat4f _pvw_transformation;
    Mat4f _wvp_transformation;
    Mat4f _w_transformation;
    Mat4f _v_transformation;
    Mat4f _proj_transformation;
};


#endif /* pipeline_hpp */
