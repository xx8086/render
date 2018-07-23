//
//  quaternion.cpp
//  megranate
//
//  Created by liu on 2018/7/9.
//  Copyright © 2018年 hanliu. All rights reserved.
//
/*
#include "quaternion.hpp"
#include "math_common.hpp"
#include <math.h>

namespace megranate {
    
    void Quaternion::from_angle_axis(float angle, const Vec3f& axis){
        angle *= M_DEGTORAD_2;
        w = cosf(angle);
        float sin_angle = sinf(angle);
        const Vec3f norm_axis = axis.normalized();
        x = norm_axis.x * sin_angle;
        y = norm_axis.y * sin_angle;
        z = norm_axis.z * sin_angle;
    }
    
    
    void Quaternion::from_euler_angles(float x, float y, float z){
        x *= M_DEGTORAD_2;
        y *= M_DEGTORAD_2;
        z *= M_DEGTORAD_2;
        float sinX = sinf(x);
        float cosX = cosf(x);
        float sinY = sinf(y);
        float cosY = cosf(y);
        float sinZ = sinf(z);
        float cosZ = cosf(z);
        
        w = cosY * cosX * cosZ + sinY * sinX * sinZ;
        x = cosY * sinX * cosZ + sinY * cosX * sinZ;
        y = sinY * cosX * cosZ - cosY * sinX * sinZ;
        z = cosY * cosX * sinZ - sinY * sinX * cosZ;
    }
    
    void Quaternion::from_rotation_to(const Vec3f& start, const Vec3f& end){
        Vec3f normStart = start.normalized();
        Vec3f normEnd = end.normalized();
        float d = normStart.dot(normEnd);
        
        if (d > -1.0f + M_EPSILON)
        {
            Vec3f c = cross(normStart, normEnd);
            float s = sqrtf((1.0f + d) * 2.0f);
            float invS = 1.0f / s;
            
            x = c.x * invS;
            y = c.y * invS;
            z = c.z * invS;
            w = 0.5f * s;
        }
        else
        {
            Vec3f axis = cross(RIGHT, normStart);
            if (axis.length() < M_EPSILON)
                axis = cross(UP, normStart);
            
            from_angle_axis(180.f, axis);
        }
    }
    
    void Quaternion::from_axes(const Vec3f& xAxis, const Vec3f& yAxis, const Vec3f& zAxis){
        Mat3f matrix(xAxis.x, yAxis.x, zAxis.x,
                     xAxis.y, yAxis.y, zAxis.y,
                     xAxis.z, yAxis.z, zAxis.z);
        from_rotation_matrix(matrix);
    }
    
    void Quaternion::from_rotation_matrix(const Mat3f& matrix){
        float t = matrix.m[0][0] + matrix.m[1][1] + matrix.m[2][2];
        if (t > 0.0f){
            float invS = 0.5f / sqrtf(1.0f + t);
            
            x = (matrix.m[2][1] - matrix.m[1][2]) * invS;
            y = (matrix.m[0][2] - matrix.m[2][0]) * invS;
            z = (matrix.m[1][0] - matrix.m[0][1]) * invS;
            w = 0.25f / invS;
        }
        else{
            if (matrix.m[0][0] > matrix.m[1][1] && matrix.m[0][0] > matrix.m[2][2]){
                float invS = 0.5f / sqrtf(1.0f + matrix.m[0][0] - matrix.m[1][1] - matrix.m[2][2]);
                
                x = 0.25f / invS;
                y = (matrix.m[0][1] + matrix.m[1][0]) * invS;
                z = (matrix.m[2][0] + matrix.m[0][2]) * invS;
                w = (matrix.m[2][1] - matrix.m[1][2]) * invS;
            }
            else if (matrix.m[1][1] > matrix.m[2][2]){
                float invS = 0.5f / sqrtf(1.0f + matrix.m[1][1] - matrix.m[0][0] - matrix.m[2][2]);
                
                x = (matrix.m[0][1] + matrix.m[1][0]) * invS;
                y = 0.25f / invS;
                z = (matrix.m[1][2] + matrix.m[2][1]) * invS;
                w = (matrix.m[0][2] - matrix.m[2][0]) * invS;
            }
            else{
                float invS = 0.5f / sqrtf(1.0f + matrix.m[2][2] - matrix.m[0][0] - matrix.m[1][1]);
                
                x = (matrix.m[0][2] + matrix.m[2][0]) * invS;
                y = (matrix.m[1][2] + matrix.m[2][1]) * invS;
                z = 0.25f / invS;
                w = (matrix.m[1][0] - matrix.m[0][1]) * invS;
            }
        }
    }
    
    
    bool Quaternion::from_look_rotation(const Vec3f& direction, const Vec3f& upDirection){
        Quaternion ret;
        Vec3f forward = direction.normalized();
        Vec3f v = cross(forward, upDirection);
        if (v.length_squared() >= M_EPSILON){
            v.normalize();
            Vec3f up = cross(v, forward);
            Vec3f right = cross(up, forward);
            ret.from_axes(right, up, forward);
        }
        else
            ret.from_rotation_to(FORWARD, forward);
        
        if (!ret.is_nan()){
            (*this) = ret;
            return true;
        }
        else
            return false;
    }
    
    Vec3f Quaternion::euler_angles() const{
        // Derivation from http://www.geometrictools.com/Documentation/EulerAngles.pdf
        // Order of rotations: Z first, then X, then Y
        float check = 2.0f * (-y * z + w * x);
        
        if (check < -0.995f){
            return Vec3f(
                           -90.0f,
                           0.0f,
                           -atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * M_RADTODEG
                           );
        }
        else if (check > 0.995f){
            return Vec3f(
                           90.0f,
                           0.0f,
                           atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * M_RADTODEG
                           );
        }
        else{
            return Vec3f(
                           asinf(check) * M_RADTODEG,
                           atan2f(2.0f * (x * z + w * y), 1.0f - 2.0f * (x * x + y * y)) * M_RADTODEG,
                           atan2f(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z)) * M_RADTODEG
                           );
        }
    }
    
    float Quaternion::yaw_angle() const{
        return euler_angles().y;
    }
    
    float Quaternion::pitch_angle() const{
        return euler_angles().x;
    }
    
    float Quaternion::roll_angle() const{
        return euler_angles().z;
    }
    
    Vec3f Quaternion::axis() const{
        const float d = 1.0f / sqrtf(1.0 - w * w);
        return Vec3f(x * d, y * d, z * d) ;
    }
    
    float Quaternion::angle() const{
        return 2 * cosf(w);
    }
    
    Mat3f Quaternion::rotation_matrix() const{
        return Mat3f(  1.0f - 2.0f * y * y - 2.0f * z * z,
                       2.0f * x * y - 2.0f * w * z,
                       2.0f * x * z + 2.0f * w * y,
                     
                       2.0f * x * y + 2.0f * w * z,
                       1.0f - 2.0f * x * x - 2.0f * z * z,
                       2.0f * y * z - 2.0f * w * x,
                     
                       2.0f * x * z - 2.0f * w * y,
                       2.0f * y * z + 2.0f * w * x,
                       1.0f - 2.0f * x * x - 2.0f * y * y);
    }
    
    Quaternion Quaternion::slerp(const Quaternion& rhs, float t) const{
#if 0
        float angle = DotProduct(rhs);
        float sign = 1.f; // Multiply by a sign of +/-1 to guarantee we rotate the shorter arc.
        if (angle < 0.f){
            angle = -angle;
            sign = -1.f;
        }
        
        float a;
        float b;
        if (angle < 0.999f) // perform spherical linear interpolation.
        {
            // angle = acos(angle); // After this, angle is in the range pi/2 -> 0 as the original angle variable ranged from 0 -> 1.
            angle = (-0.69813170079773212f * angle * angle - 0.87266462599716477f) * angle + 1.5707963267948966f;
            float ta = t*angle;
            // Manually compute the two sines by using a very rough approximation.
            float ta2 = ta*ta;
            b = ((5.64311797634681035370e-03f * ta2 - 1.55271410633428644799e-01f) * ta2 + 9.87862135574673806965e-01f) * ta;
            a = angle - ta;
            float a2 = a*a;
            a = ((5.64311797634681035370e-03f * a2 - 1.55271410633428644799e-01f) * a2 + 9.87862135574673806965e-01f) * a;
        }
        else // If angle is close to taking the denominator to zero, resort to linear interpolation (and normalization).
        {
            a = 1.f - t;
            b = t;
        }
        // Lerp and renormalize.
        return (*this * (a * sign) + rhs * b).normalized();
#else
        // Favor accuracy for native code builds
        float cosAngle = dot(rhs);
        float sign = 1.0f;
        // Enable shortest path rotation
        if (cosAngle < 0.0f)
        {
            cosAngle = -cosAngle;
            sign = -1.0f;
        }
        
        float angle = acosf(cosAngle);
        float sinAngle = sinf(angle);
        float t1, t2;
        
        if (sinAngle > 0.001f)
        {
            float invSinAngle = 1.0f / sinAngle;
            t1 = sinf((1.0f - t) * angle) * invSinAngle;
            t2 = sinf(t * angle) * invSinAngle;
        }
        else
        {
            t1 = 1.0f - t;
            t2 = t;
        }
        
        return (*this) * t1 + (rhs * sign) * t2;
#endif
    }
 
    Quaternion Quaternion::nlerp(const Quaternion& rhs, float t, bool shortestPath) const{
        Quaternion result;
        float fCos = dot(rhs);
        if (fCos < 0.0f && shortestPath)
            result = (*this) - (rhs + (*this) * t);
        else
            result = (*this) + ((rhs - (*this)) * t);
        result.normalize();
        return result;
    }
    
    Vec3f Quaternion::operator* (const Vec3f& rhs) const{
        Vec3f qvec(x, y, z);
        Vec3f cross1(cross(qvec, rhs));
        Vec3f cross2(cross(qvec, cross1));
        cross1 *= w;
        cross1 += cross2;
        cross1 *= 2.0f;
        cross1 += rhs;
        return cross1;
    }

}
 */
