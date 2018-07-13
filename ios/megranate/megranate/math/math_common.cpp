//
//  math_common.cpp
//  megranate
//
//  Created by liu on 2018/7/9.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "math_common.hpp"
#include "config_render.h"

namespace megranate {
    float determinant(const Mat4f& mat4f)
    {
        return mat4f.m[0][0]*mat4f.m[1][1]*mat4f.m[2][2]*mat4f.m[3][3] - mat4f.m[0][0]*mat4f.m[1][1]*mat4f.m[2][3]*mat4f.m[3][2] + mat4f.m[0][0]*mat4f.m[1][2]*mat4f.m[2][3]*mat4f.m[3][1] - mat4f.m[0][0]*mat4f.m[1][2]*mat4f.m[2][1]*mat4f.m[3][3]
        + mat4f.m[0][0]*mat4f.m[1][3]*mat4f.m[2][1]*mat4f.m[3][2] - mat4f.m[0][0]*mat4f.m[1][3]*mat4f.m[2][2]*mat4f.m[3][1] - mat4f.m[0][1]*mat4f.m[1][2]*mat4f.m[2][3]*mat4f.m[3][0] + mat4f.m[0][1]*mat4f.m[1][2]*mat4f.m[2][0]*mat4f.m[3][3]
        - mat4f.m[0][1]*mat4f.m[1][3]*mat4f.m[2][0]*mat4f.m[3][2] + mat4f.m[0][1]*mat4f.m[1][3]*mat4f.m[2][2]*mat4f.m[3][0] - mat4f.m[0][1]*mat4f.m[1][0]*mat4f.m[2][2]*mat4f.m[3][3] + mat4f.m[0][1]*mat4f.m[1][0]*mat4f.m[2][3]*mat4f.m[3][2]
        + mat4f.m[0][2]*mat4f.m[1][3]*mat4f.m[2][0]*mat4f.m[3][1] - mat4f.m[0][2]*mat4f.m[1][3]*mat4f.m[2][1]*mat4f.m[3][0] + mat4f.m[0][2]*mat4f.m[1][0]*mat4f.m[2][1]*mat4f.m[3][3] - mat4f.m[0][2]*mat4f.m[1][0]*mat4f.m[2][3]*mat4f.m[3][1]
        + mat4f.m[0][2]*mat4f.m[1][1]*mat4f.m[2][3]*mat4f.m[3][0] - mat4f.m[0][2]*mat4f.m[1][1]*mat4f.m[2][0]*mat4f.m[3][3] - mat4f.m[0][3]*mat4f.m[1][0]*mat4f.m[2][1]*mat4f.m[3][2] + mat4f.m[0][3]*mat4f.m[1][0]*mat4f.m[2][2]*mat4f.m[3][1]
        - mat4f.m[0][3]*mat4f.m[1][1]*mat4f.m[2][2]*mat4f.m[3][0] + mat4f.m[0][3]*mat4f.m[1][1]*mat4f.m[2][0]*mat4f.m[3][2] - mat4f.m[0][3]*mat4f.m[1][2]*mat4f.m[2][0]*mat4f.m[3][1] + mat4f.m[0][3]*mat4f.m[1][2]*mat4f.m[2][1]*mat4f.m[3][0];
    }
    
    void inverse(Mat4f& mat4f)
    {
        float det = determinant(mat4f);
        if(det == 0.0f){
            // Matrix not invertible. Setting all elements to nan is not really
            // correct in a mathematical sense but it is easy to debug for the
            // programmer.
            /*const float nan = std::numeric_limits<float>::quiet_NaN();
             *this = Matrix4f(
             nan,nan,nan,nan,
             nan,nan,nan,nan,
             nan,nan,nan,nan,
             nan,nan,nan,nan);*/
            assert(0);
            return;
        }
        
        float invdet = 1.0f / det;
        Mat4f res;
        res.m[0][0] = invdet  * (mat4f.m[1][1] * (mat4f.m[2][2] * mat4f.m[3][3] - mat4f.m[2][3] * mat4f.m[3][2]) + mat4f.m[1][2] * (mat4f.m[2][3] * mat4f.m[3][1] - mat4f.m[2][1] * mat4f.m[3][3]) + mat4f.m[1][3] * (mat4f.m[2][1] * mat4f.m[3][2] - mat4f.m[2][2] * mat4f.m[3][1]));
        res.m[0][1] = -invdet * (mat4f.m[0][1] * (mat4f.m[2][2] * mat4f.m[3][3] - mat4f.m[2][3] * mat4f.m[3][2]) + mat4f.m[0][2] * (mat4f.m[2][3] * mat4f.m[3][1] - mat4f.m[2][1] * mat4f.m[3][3]) + mat4f.m[0][3] * (mat4f.m[2][1] * mat4f.m[3][2] - mat4f.m[2][2] * mat4f.m[3][1]));
        res.m[0][2] = invdet  * (mat4f.m[0][1] * (mat4f.m[1][2] * mat4f.m[3][3] - mat4f.m[1][3] * mat4f.m[3][2]) + mat4f.m[0][2] * (mat4f.m[1][3] * mat4f.m[3][1] - mat4f.m[1][1] * mat4f.m[3][3]) + mat4f.m[0][3] * (mat4f.m[1][1] * mat4f.m[3][2] - mat4f.m[1][2] * mat4f.m[3][1]));
        res.m[0][3] = -invdet * (mat4f.m[0][1] * (mat4f.m[1][2] * mat4f.m[2][3] - mat4f.m[1][3] * mat4f.m[2][2]) + mat4f.m[0][2] * (mat4f.m[1][3] * mat4f.m[2][1] - mat4f.m[1][1] * mat4f.m[2][3]) + mat4f.m[0][3] * (mat4f.m[1][1] * mat4f.m[2][2] - mat4f.m[1][2] * mat4f.m[2][1]));
        res.m[1][0] = -invdet * (mat4f.m[1][0] * (mat4f.m[2][2] * mat4f.m[3][3] - mat4f.m[2][3] * mat4f.m[3][2]) + mat4f.m[1][2] * (mat4f.m[2][3] * mat4f.m[3][0] - mat4f.m[2][0] * mat4f.m[3][3]) + mat4f.m[1][3] * (mat4f.m[2][0] * mat4f.m[3][2] - mat4f.m[2][2] * mat4f.m[3][0]));
        res.m[1][1] = invdet  * (mat4f.m[0][0] * (mat4f.m[2][2] * mat4f.m[3][3] - mat4f.m[2][3] * mat4f.m[3][2]) + mat4f.m[0][2] * (mat4f.m[2][3] * mat4f.m[3][0] - mat4f.m[2][0] * mat4f.m[3][3]) + mat4f.m[0][3] * (mat4f.m[2][0] * mat4f.m[3][2] - mat4f.m[2][2] * mat4f.m[3][0]));
        res.m[1][2] = -invdet * (mat4f.m[0][0] * (mat4f.m[1][2] * mat4f.m[3][3] - mat4f.m[1][3] * mat4f.m[3][2]) + mat4f.m[0][2] * (mat4f.m[1][3] * mat4f.m[3][0] - mat4f.m[1][0] * mat4f.m[3][3]) + mat4f.m[0][3] * (mat4f.m[1][0] * mat4f.m[3][2] - mat4f.m[1][2] * mat4f.m[3][0]));
        res.m[1][3] = invdet  * (mat4f.m[0][0] * (mat4f.m[1][2] * mat4f.m[2][3] - mat4f.m[1][3] * mat4f.m[2][2]) + mat4f.m[0][2] * (mat4f.m[1][3] * mat4f.m[2][0] - mat4f.m[1][0] * mat4f.m[2][3]) + mat4f.m[0][3] * (mat4f.m[1][0] * mat4f.m[2][2] - mat4f.m[1][2] * mat4f.m[2][0]));
        res.m[2][0] = invdet  * (mat4f.m[1][0] * (mat4f.m[2][1] * mat4f.m[3][3] - mat4f.m[2][3] * mat4f.m[3][1]) + mat4f.m[1][1] * (mat4f.m[2][3] * mat4f.m[3][0] - mat4f.m[2][0] * mat4f.m[3][3]) + mat4f.m[1][3] * (mat4f.m[2][0] * mat4f.m[3][1] - mat4f.m[2][1] * mat4f.m[3][0]));
        res.m[2][1] = -invdet * (mat4f.m[0][0] * (mat4f.m[2][1] * mat4f.m[3][3] - mat4f.m[2][3] * mat4f.m[3][1]) + mat4f.m[0][1] * (mat4f.m[2][3] * mat4f.m[3][0] - mat4f.m[2][0] * mat4f.m[3][3]) + mat4f.m[0][3] * (mat4f.m[2][0] * mat4f.m[3][1] - mat4f.m[2][1] * mat4f.m[3][0]));
        res.m[2][2] = invdet  * (mat4f.m[0][0] * (mat4f.m[1][1] * mat4f.m[3][3] - mat4f.m[1][3] * mat4f.m[3][1]) + mat4f.m[0][1] * (mat4f.m[1][3] * mat4f.m[3][0] - mat4f.m[1][0] * mat4f.m[3][3]) + mat4f.m[0][3] * (mat4f.m[1][0] * mat4f.m[3][1] - mat4f.m[1][1] * mat4f.m[3][0]));
        res.m[2][3] = -invdet * (mat4f.m[0][0] * (mat4f.m[1][1] * mat4f.m[2][3] - mat4f.m[1][3] * mat4f.m[2][1]) + mat4f.m[0][1] * (mat4f.m[1][3] * mat4f.m[2][0] - mat4f.m[1][0] * mat4f.m[2][3]) + mat4f.m[0][3] * (mat4f.m[1][0] * mat4f.m[2][1] - mat4f.m[1][1] * mat4f.m[2][0]));
        res.m[3][0] = -invdet * (mat4f.m[1][0] * (mat4f.m[2][1] * mat4f.m[3][2] - mat4f.m[2][2] * mat4f.m[3][1]) + mat4f.m[1][1] * (mat4f.m[2][2] * mat4f.m[3][0] - mat4f.m[2][0] * mat4f.m[3][2]) + mat4f.m[1][2] * (mat4f.m[2][0] * mat4f.m[3][1] - mat4f.m[2][1] * mat4f.m[3][0]));
        res.m[3][1] = invdet  * (mat4f.m[0][0] * (mat4f.m[2][1] * mat4f.m[3][2] - mat4f.m[2][2] * mat4f.m[3][1]) + mat4f.m[0][1] * (mat4f.m[2][2] * mat4f.m[3][0] - mat4f.m[2][0] * mat4f.m[3][2]) + mat4f.m[0][2] * (mat4f.m[2][0] * mat4f.m[3][1] - mat4f.m[2][1] * mat4f.m[3][0]));
        res.m[3][2] = -invdet * (mat4f.m[0][0] * (mat4f.m[1][1] * mat4f.m[3][2] - mat4f.m[1][2] * mat4f.m[3][1]) + mat4f.m[0][1] * (mat4f.m[1][2] * mat4f.m[3][0] - mat4f.m[1][0] * mat4f.m[3][2]) + mat4f.m[0][2] * (mat4f.m[1][0] * mat4f.m[3][1] - mat4f.m[1][1] * mat4f.m[3][0]));
        res.m[3][3] = invdet  * (mat4f.m[0][0] * (mat4f.m[1][1] * mat4f.m[2][2] - mat4f.m[1][2] * mat4f.m[2][1]) + mat4f.m[0][1] * (mat4f.m[1][2] * mat4f.m[2][0] - mat4f.m[1][0] * mat4f.m[2][2]) + mat4f.m[0][2] * (mat4f.m[1][0] * mat4f.m[2][1] - mat4f.m[1][1] * mat4f.m[2][0]));
        
        mat4f = res;
    }
    
    void init_mat_scale(Mat4f& mt4, float x, float y, float z){
        mt4.m[0][0] = x; mt4.m[0][1] = 0.0f;   mt4.m[0][2] = 0.0f;   mt4.m[0][3] = 0.0f;
        mt4.m[1][0] = 0.0f;   mt4.m[1][1] = y; mt4.m[1][2] = 0.0f;   mt4.m[1][3] = 0.0f;
        mt4.m[2][0] = 0.0f;   mt4.m[2][1] = 0.0f;   mt4.m[2][2] = z; mt4.m[2][3] = 0.0f;
        mt4.m[3][0] = 0.0f;   mt4.m[3][1] = 0.0f;   mt4.m[3][2] = 0.0f;   mt4.m[3][3] = 1.0f;
    }
    
    void init_mat_translation(Mat4f& mt4, float x, float y, float z){
        mt4.m[0][0] = 1.0f; mt4.m[0][1] = 0.0f; mt4.m[0][2] = 0.0f; mt4.m[0][3] = x;
        mt4.m[1][0] = 0.0f; mt4.m[1][1] = 1.0f; mt4.m[1][2] = 0.0f; mt4.m[1][3] = y;
        mt4.m[2][0] = 0.0f; mt4.m[2][1] = 0.0f; mt4.m[2][2] = 1.0f; mt4.m[2][3] = z;
        mt4.m[3][0] = 0.0f; mt4.m[3][1] = 0.0f; mt4.m[3][2] = 0.0f; mt4.m[3][3] = 1.0f;
    }
    
    void init_rotate_transform(Mat4f& mt4, float rotate_x, float rotate_y, float rotate_z){
        Mat4f rx, ry, rz;
        const float x = ToRadian(rotate_x);
        const float y = ToRadian(rotate_y);
        const float z = ToRadian(rotate_z);
        
        rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f   ; rx.m[0][2] = 0.0f    ; rx.m[0][3] = 0.0f;
        rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(x); rx.m[1][2] = -sinf(x); rx.m[1][3] = 0.0f;
        rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(x); rx.m[2][2] = cosf(x) ; rx.m[2][3] = 0.0f;
        rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f   ; rx.m[3][2] = 0.0f    ; rx.m[3][3] = 1.0f;
        
        ry.m[0][0] = cosf(y); ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(y); ry.m[0][3] = 0.0f;
        ry.m[1][0] = 0.0f   ; ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f    ; ry.m[1][3] = 0.0f;
        ry.m[2][0] = sinf(y); ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(y) ; ry.m[2][3] = 0.0f;
        ry.m[3][0] = 0.0f   ; ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f    ; ry.m[3][3] = 1.0f;
        
        rz.m[0][0] = cosf(z); rz.m[0][1] = -sinf(z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
        rz.m[1][0] = sinf(z); rz.m[1][1] = cosf(z) ; rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
        rz.m[2][0] = 0.0f   ; rz.m[2][1] = 0.0f    ; rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
        rz.m[3][0] = 0.0f   ; rz.m[3][1] = 0.0f    ; rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;
        
        mt4 = rz * ry * rx;
    }
    
    void init_camera_transform(Mat4f& mt4, const Vec3f& Target, const Vec3f& Up){
        Vec3f N = Target;
        N.normalize();
        Vec3f U = Up;
        U = cross(U, N);
        U.normalize();
        Vec3f V = cross(N, U);
        
        mt4.m[0][0] = U.x;   mt4.m[0][1] = U.y;   mt4.m[0][2] = U.z;   mt4.m[0][3] = 0.0f;
        mt4.m[1][0] = V.x;   mt4.m[1][1] = V.y;   mt4.m[1][2] = V.z;   mt4.m[1][3] = 0.0f;
        mt4.m[2][0] = N.x;   mt4.m[2][1] = N.y;   mt4.m[2][2] = N.z;   mt4.m[2][3] = 0.0f;
        mt4.m[3][0] = 0.0f;  mt4.m[3][1] = 0.0f;  mt4.m[3][2] = 0.0f;  mt4.m[3][3] = 1.0f;
    }

    
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
