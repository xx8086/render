//
//  context.cpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "context.h"

namespace megranate {
    Object* Context::get_sub_system(StringHash key) const{
        auto search = _sub_system.find(key);
        if (search != _sub_system.end()) {
            return search->second;//*(search->second).get();
        }
        return nullptr;
    }
}
