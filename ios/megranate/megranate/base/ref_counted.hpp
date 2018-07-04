//
//  ref_counted.hpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef ref_counted_hpp
#define ref_counted_hpp

#include "base_type.h"

namespace megranate {
    struct RefCount{
        RefCount():
            _refs(0),
            _weak_refs(0){
        }
        
        ~RefCount(){
            _refs = -1;
            _weak_refs = -1;
        }
        
        mg_int _refs;
        mg_int _weak_refs;
    };
    
    class RefCounted{
    public:
        RefCounted();
        ~RefCounted();
    public:
        mg_void add_ref();
        mg_void release_ref();
        mg_int refs() const;
        mg_int weak_refs() const;
        RefCount* ref_count_ptr(){ return _ref_count;};
    private:
        RefCounted(const RefCounted& rhs);
        RefCounted& operator= (const RefCounted& rhs);
    private:
        RefCount* _ref_count;
    };
}

#endif /* ref_counted_hpp */
