//
//  type_render.h
//  megranate
//
//  Created by liu on 2018/7/8.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef type_render_h
#define type_render_h

#include "../math/vertex.hpp"
#include "../math/matrix.hpp"

namespace megranate {
typedef  MgVertex<float, 2> Vec2f;
typedef  MgVertex<float, 3> Vec3f;
typedef  MgVertex<float, 4> Vec4f;
typedef  MgVertex<int, 2> Vec2i;
typedef  MgVertex<int, 3> Vec3i;
typedef  MgVertex<int, 4> Vec4i;

typedef MgMatrix<float, 3, 3> Mat3f;
typedef MgMatrix<float, 4, 4> Mat4f;
typedef MgMatrix<float, 3, 4> Mat3x4f;
typedef MgMatrix<int, 3, 3> Mat3i;
typedef MgMatrix<int, 4, 4> Mat4i;

    
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
