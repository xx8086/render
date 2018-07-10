//
//  math_common.cpp
//  megranate
//
//  Created by liu on 2018/7/9.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "math_common.hpp"

namespace megranate {
    Vec3f cross(const Vec3f& left, const Vec3f& right){
        return Vec3f(left.y * right.z - left.z * right.y,
                     left.z * right.x - left.x * right.z,
                     left.x * right.y - left.y * right.x);
    }
    
    Mat3x4f Mat3to3_4(const Mat3f& m3f){
        Mat3x4f m34f;
        m34f.m[0][3] = 0.0f;
        m34f.m[1][3] = 0.0f;
        m34f.m[2][3] = 0.0f;
        
        m34f.m[0][0] = m3f.m[0][0];
        m34f.m[0][1] = m3f.m[0][1];
        m34f.m[0][2] = m3f.m[0][2];
        
        m34f.m[1][0] = m3f.m[1][0];
        m34f.m[1][1] = m3f.m[1][1];
        m34f.m[1][2] = m3f.m[1][2];
        
        m34f.m[2][0] = m3f.m[2][0];
        m34f.m[2][1] = m3f.m[2][1];
        m34f.m[2][2] = m3f.m[2][2];
        
        return m34f;
    }
    Mat4f Mat3to4(const Mat3f& m3f){
        Mat4f m4f;
        m4f.m[0][3] = 0.0f;
        m4f.m[1][3] = 0.0f;
        m4f.m[2][3] = 0.0f;
        m4f.m[3][3] = 0.0f;
        
        m4f.m[0][0] = m3f.m[0][0];
        m4f.m[0][1] = m3f.m[0][1];
        m4f.m[0][2] = m3f.m[0][2];
        
        m4f.m[1][0] = m3f.m[1][0];
        m4f.m[1][1] = m3f.m[1][1];
        m4f.m[1][2] = m3f.m[1][2];
        
        m4f.m[2][0] = m3f.m[2][0];
        m4f.m[2][1] = m3f.m[2][1];
        m4f.m[2][2] = m3f.m[2][2];
        
        return m4f;
    }
}
