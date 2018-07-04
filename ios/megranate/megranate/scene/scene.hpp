//
//  scene.hpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef scene_hpp
#define scene_hpp

#include "entity.hpp"
#include <map>

namespace megranate {
    class Scene : public Object{
    public:
        Scene(Context* context);
        ~Scene();
    public:
        mg_bool update();
    public:
        mg_bool insert_entity(Entity*);
        mg_bool insert_orth(Entity*);
    private:
        mg_void release();
    private:
        std::map<StringHash, Entity*> _entities;
        Entity* _root = nullptr;
        std::string _dir;
    };
}

#endif /* scene_hpp */
