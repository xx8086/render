//
//  math_common.hpp
//  megranate
//
//  Created by liu on 2018/7/9.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef math_common_hpp
#define math_common_hpp

#include <stdio.h>
#include "../object/type_render.h"
namespace megranate {
    Vec3f cross(const Vec3f&, const Vec3f&);
    Mat4f Mat3to4(const Mat3f&);
    Mat3x4f Mat3to3_4(const Mat3f&);
    void init_mat_scale(Mat4f&, float, float, float);
    void init_mat_translation(Mat4f&, float, float, float);
    void init_rotate_transform(Mat4f&, float, float, float);
    void init_camera_transform(Mat4f& mt4, const Vec3f& Target, const Vec3f& Up);
    float determinant(const Mat4f& mat4f);
    void inverse(Mat4f& mat4f);
    
    //void InitPersProjTransform(const PersProjInfo& p);
    //void InitOrthoProjTransform(const OrthoProjInfo& p);
    //void InitRotateTransform(const Quaternion& quat);
}
#endif /* math_common_hpp */
