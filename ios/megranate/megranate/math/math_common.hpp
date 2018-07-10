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
#include "../base/type_render.h"
namespace megranate {
Vec3f cross(const Vec3f&, const Vec3f&);
Mat4f Mat3to4(const Mat3f&);
Mat3x4f Mat3to3_4(const Mat3f&);
}
#endif /* math_common_hpp */
