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
#include "object.h"

namespace megranate {
    class Context : public RefCounted{
    public:
        ~Context();
        Object* create_object(StringHash key);
        Object* get_sub_system(StringHash key) const;
        void remove_sub_system(StringHash key);
        
        template<typename T>
        void register_factory(){
            register_factory(new ObjectFactoryImpl<T>(this));
        }
    private:
        void register_factory(ObjectFactory*);
        
    private:
        //std::unordered_map<StringHash, std::shared_ptr<Object*> > _sub_system;
        std::map<StringHash, Object*> _sub_system;
        std::map<StringHash, ObjectFactory*> _factories;
    };
}

#endif /* context_hpp */
