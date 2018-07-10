//
//  type_render.h
//  megranate
//
//  Created by liu on 2018/7/8.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef type_render_h
#define type_render_h

#include "vertex.hpp"
#include "matrix.hpp"
namespace megranate {
typedef  megranate::MgVertex<float, 2> Vec2f;
typedef  megranate::MgVertex<float, 3> Vec3f;
typedef  megranate::MgVertex<float, 4> Vec4f;
typedef  megranate::MgVertex<int, 2> Vec2i;
typedef  megranate::MgVertex<int, 3> Vec3i;
typedef  megranate::MgVertex<int, 4> Vec4i;

typedef megranate::MgMatrix<float, 3, 3> Mat3f;
typedef megranate::MgMatrix<float, 4, 4> Mat4f;
typedef megranate::MgMatrix<int, 3, 3> Mat3i;
typedef megranate::MgMatrix<int, 4, 4> Mat4i;

    
    /// Zero vector.
    static const Vec3f ZERO(0, 0, 0);
    /// (-1,0,0) vector.
    static const Vec3f LEFT(-1, 0, 0);
    /// (1,0,0) vector.
    static const Vec3f RIGHT(1, 0, 0);
    /// (0,1,0) vector.
    static const Vec3f UP(0, 1, 0);
    /// (0,-1,0) vector.
    static const Vec3f DOWN(0, -1, 0);
    /// (0,0,1) vector.
    static const Vec3f FORWARD(0, 0, 1);
    /// (0,0,-1) vector.
    static const Vec3f BACK(0, 0, -1);
    /// (1,1,1) vector.
    static const Vec3f ONE(1, 1, 1);
}

#endif /* type_render_h */
