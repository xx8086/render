//
//  quaternion.hpp
//  megranate
//
//  Created by liu on 2018/7/9.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef quaternion_hpp
#define quaternion_hpp

#include "../base/type_render.h"
#include "../base/config_render.h"

namespace megranate {
    class Quaternion{
    public:
        typedef ArithmeticalPolicy<float> APF;
        ~Quaternion();
        Quaternion():w(1.0f), x(0.0f), y(0.0f), z(0.0f){}
        Quaternion(const Quaternion& other):
        w(other.w), x(other.x), y(other.y), z(other.z){}
        Quaternion(float tw, float tx, float ty, float tz):
        w(tw), x(tx), y(ty), z(tz){}
        
        Quaternion(float angle, const Vec3f& axis){
            from_angle_axis(angle, axis);
        }
        
        explicit Quaternion(float angle){
            from_angle_axis(angle, FORWARD);
        }
        
        /// Construct from Euler angles (in degrees.)
        Quaternion(float x, float y, float z){
            from_euler_angles(x, y, z);
        }
        
        /// Construct from the rotation difference between two direction vectors.
        Quaternion(const Vec3f& start, const Vec3f& end){
            from_rotation_to(start, end);
        }
        
        /// Construct from orthonormal axes.
        Quaternion(const Vec3f& xAxis, const Vec3f& yAxis, const Vec3f& zAxis){
            from_axes(xAxis, yAxis, zAxis);
        }
    public:
        Vec3f operator* (const Vec3f& rhs) const;
        
        Quaternion operator* (const float t) const{
            return Quaternion(t*w, t*x, t* y, t*z);
        }
        
        Quaternion& operator =(const Quaternion& rhs){
            w = rhs.w;
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            return *this;
        }
        
        Quaternion operator +(const Quaternion& rhs) const{
            return Quaternion(w + rhs.w,
                              x + rhs.x,
                              y + rhs.y,
                              z + rhs.z);
        }
        
        Quaternion operator -(const Quaternion& rhs) const{
            return Quaternion(w - rhs.w,
                              x - rhs.x,
                              y - rhs.y,
                              z - rhs.z);
        }
        
        Quaternion& operator +=(const Quaternion& rhs){
            w += rhs.w;
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        Quaternion& operator *=(float rhs){
            w *= rhs;
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }
        
        bool operator ==(const Quaternion& rhs){
            return (w == rhs.w &&
                    x == rhs.x &&
                    y == rhs.y &&
                    z == rhs.z);
        }
    public:
        void from_angle_axis(float angle, const Vec3f& axis);
        void from_euler_angles(float x, float y, float z);
        void from_rotation_to(const Vec3f& start, const Vec3f& end);
        void from_axes(const Vec3f& xAxis, const Vec3f& yAxis, const Vec3f& zAxis);
        bool from_look_rotation(const Vec3f& direction, const Vec3f& up = UP);
        
        bool is_nan()const{
            return (nan(w) ||
            nan(x) ||
            nan(y) ||
            nan(z));
        }
        bool equals(const Quaternion& rhs)const{
            return (APF::equal(w, rhs.w) &&
            APF::equal(x, rhs.x) &&
            APF::equal(y, rhs.y) &&
            APF::equal(z, rhs.z));
        }
        Quaternion conjuate() const{
            return Quaternion(-w, -x, -y, -z);
        }
        float dot(const Quaternion& rhs)const{
            return (w*rhs.w + x*rhs.x + y*rhs.y + z*rhs.z);
        }
        float length_squared() const{
            return (w*w + x*x + y*y + z*z);
        }
        void normalize(){
            float length = length_squared();
            if (length > 0.0f && !APF::equal(length, 1.0f)){
                float invlen = 1.0f / sqrtf(length);
                w *= invlen;
                x *= invlen;
                y *= invlen;
                z *= invlen;
            }
        }
        Quaternion normalized() const{
            float length = length_squared();
            if (length > 0.0f && !APF::equal(length, 1.0f)){
                float invlen = 1.0f / sqrtf(length);
                return (*this) * invlen;
            }
            return *this;
        }
        Quaternion inveres()const{
            float length = length_squared();
            if(APF::equal(length, 1.0f)){
                return conjuate();
            }
            else if(length >= M_EPSILON){
                return conjuate() * (1.0f / length);
            }
            return Quaternion();
        }
        
        void from_rotation_matrix(const Mat3f& );
        
        Vec3f euler_angles() const;
        float yaw_angle() const;
        float pitch_angle() const;
        float roll_angle() const;
        float angle() const;
        Vec3f axis() const;
        Mat3f rotation_matrix() const;
        Quaternion slerp(const Quaternion& rhs, float t) const;
        Quaternion nlerp(const Quaternion& rhs, float t, bool shortestPath = false) const;
    public:
        float w;
        float x;
        float y;
        float z;
    };

}

#endif 

