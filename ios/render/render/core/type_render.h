//
//  type_render.h
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef type_render_h
#define type_render_h

#include "math.hpp"
typedef Matrix4f Mat4f;
typedef Vector4f Vec4f;
typedef Vector3f Vec3f;
typedef Vector2f Vec2f;


#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(ptr) \
if(nullptr != ptr){\
delete ptr;\
ptr = nullptr;\
}
#endif /* type_render_h */
