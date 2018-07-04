//
//  entity.hpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef entity_hpp
#define entity_hpp

#include "object.h"
#include <vector>
namespace megranate {
    class Entity : public Object{
    public:
        Entity(Context* context);
    public:
        mg_bool draw();
        mg_bool update();

    public:
        mg_bool is_visible() const{return _visible;}
        void set_visible(mg_bool v){_visible = v;}
        
    private:
        mg_bool _visible = false;
        Entity* _father = nullptr;
        std::vector<Entity*> _children;
    };
}

#endif /* entity_hpp */
