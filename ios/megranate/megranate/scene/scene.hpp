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
        MEGRANATE_OBJECT(Scene, Object);
        
    public:
        Scene(Context* context);
        ~Scene();
    public:
        Entity* create_child(std::string name, CreateMode mode = REPLICATED, unsigned int id = 0, bool temporary = false);
        mg_bool update();
    public:
        mg_bool insert_entity(Entity*);
        mg_bool insert_orth(Entity*);
    private:
        mg_void release();
        mg_void add_child(Entity* e, unsigned int index);
        Entity* create_child(unsigned id, CreateMode mode, bool temporary = false);
        
    private:
        std::map<StringHash, Entity*> _entities;
        Entity* _root = nullptr;
        std::string _dir;
    };
}

#endif /* scene_hpp */
