//
//  component.cpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "component.hpp"

namespace megranate {

    Component* Component::get_component(StringHash type) const{
        return nullptr != _entity ? _entity->get_component(type) : nullptr;
    }
}
