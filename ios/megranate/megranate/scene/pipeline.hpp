//
//  pipeline.hpp
//  megranate
//
//  Created by liu on 2018/7/12.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef pipeline_hpp
#define pipeline_hpp

#include "camera.hpp"
#include "../object/base_type.h"

namespace megranate {
    
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
        
        mg_void scale(mg_float s){
            scale(s, s, s);
        }
        
        
        mg_void scale(const Vec3f& s){
            scale(s.x, s.y, s.z);
        }
        
        mg_void scale(mg_float scale_x, mg_float scale_y, mg_float scale_z){
            _scale.x = scale_x;
            _scale.y = scale_y;
            _scale.z = scale_z;
        }
        
        mg_void world_pos(mg_float x, mg_float y, mg_float z){
            _world_pos.x = x;
            _world_pos.y = y;
            _world_pos.z = z;
        }
        
        mg_void world_pos(const Vec3f& pos){
            _world_pos = pos;
        }
        
        mg_void rotate(mg_float rotate_x, mg_float rotate_y, mg_float rotate_z){
            _rotate_info.x = rotate_x;
            _rotate_info.y = rotate_y;
            _rotate_info.z = rotate_z;
        }
        
        mg_void rotate(const Vec3f& r){
            rotate(r.x, r.y, r.z);
        }
        
        mg_void set_perspective_proj(const PersProjInfo& p){
            _pers_proj_info = p;
        }
        
        mg_void set_orthographic_proj(const OrthoProjInfo& p){
            _ortho_proj_info = p;
        }
        
        mg_void set_camera(const Vec3f& pos, const Vec3f& target, const Vec3f& up){
            _camera.pos = pos;
            _camera.target = target;
            _camera.up = up;
        }
        
        mg_void orient(const Orientation& o){
            _scale      = o.scale;
            _world_pos   = o.pos;
            _rotate_info = o.rotation;
        }
        
        const Mat4f& get_wvp_trans();
        const Mat4f& get_pvw_trans();
        const Mat4f& get_world_trans();
        const Mat4f& get_view_trans();
        const Mat4f& get_proj_trans();
        
        mg_void set_wvp_trans();
        mg_void set_pvw_trans();
        mg_void set_world_trans();
        mg_void set_view_trans();
        mg_void set_proj_trans();
        
        void init_persproj_transform(Mat4f& m4f, const PersProjInfo& p);
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
}

#endif /* pipeline_hpp */
