//
//  context.hpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef context_hpp
#define context_hpp

//#include "object.h"
#include "ref_counted.hpp"
#include "string_hash.hpp"
//#include <unordered_map>
#include <map>

namespace megranate {
    class Object;
    
    class Context : public RefCounted{
        //friend class Object;
    public:
        Object* get_sub_system(StringHash key) const;
        
    private:
        //std::unordered_map<StringHash, std::shared_ptr<Object*> > _sub_system;
        std::map<StringHash, Object*> _sub_system;
    };
}

#endif /* context_hpp */
