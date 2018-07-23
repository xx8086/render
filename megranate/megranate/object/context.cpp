//
//  context.cpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "context.h"
#include "../core/skeletal.hpp"
#include "../core/fonts/font.h"
#include "../core/effect/effect.hpp"
#include <assert.h>

namespace megranate {
    
    Context::Context(){
        register_factory<Skeletal>();
        register_factory<CFont>();
        register_factory<Effect>();
    }
    
    Context::~Context(){
        _sub_system.clear();
        //_factories.clear();
    }
    
    void Context::remove_sub_system(StringHash key){
        auto search = _sub_system.find(key);
        if (search != _sub_system.end()) {
            _sub_system.erase(search);
        }
    }
    
    Object* Context::get_sub_system(StringHash key) const{
        Object* obj = nullptr;
        auto search = _sub_system.find(key);
        if (search != _sub_system.end()) {
            obj =  search->second;//*(search->second).get();
        }
        return obj;
    }
    
    void Context::register_factory(ObjectFactory* factory){
        if (_factories.find(factory->get_type()) == _factories.end()){
            _factories.emplace(std::make_pair(factory->get_type(), factory));
        }
    }
    
    Object* Context::create_object(StringHash key){
        Object* obj = nullptr;
        auto search = _factories.find(key);
        if (search != _factories.end()) {
            obj = search->second->create_object();
        }else{
            assert(false);
        }
        return obj;
    }
}
