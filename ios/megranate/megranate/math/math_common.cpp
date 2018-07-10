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
    
}
