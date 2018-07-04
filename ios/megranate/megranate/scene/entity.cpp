//
//  entity.cpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "entity.hpp"
#include <assert.h>

namespace megranate {
    Entity::Entity(Context* context) :
    Object(context){
        ;
    }
    
    mg_bool Entity::draw(){
        
        return true;
    }
    
    mg_bool Entity::update(){
        size_t children_size = _children.size();
        for(int i = 0; i < children_size; i++){
            assert(nullptr != _children[i]);
            _children[i]->update();
        }
        
        draw();
        return true;
    }
}
