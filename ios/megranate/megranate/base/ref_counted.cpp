//
//  ref_counted.cpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "debug_new.h"
#include "ref_counted.hpp"
#include "assert.h"

namespace megranate {

    RefCounted::RefCounted() :
        _ref_count(new RefCount()){
        (_ref_count->_weak_refs)++;
    }
    
    RefCounted::~RefCounted(){
        assert(_ref_count);
        assert(_ref_count->_refs == 0);
        assert(_ref_count->_weak_refs > 0);

        _ref_count->_refs = -1;
        (_ref_count->_weak_refs)--;
        if (!_ref_count->_weak_refs){
            delete _ref_count;
        }
        
        _ref_count = nullptr;
    }
    
    void RefCounted::add_ref(){
        assert(_ref_count->_refs >= 0);
        (_ref_count->_refs)++;
    }
    
    void RefCounted::release_ref(){
        assert(_ref_count->_refs > 0);
        (_ref_count->_refs)--;
        if (!_ref_count->_refs)
            delete this;
    }
    
    int RefCounted::refs() const{
        return _ref_count->_refs;
    }
}
