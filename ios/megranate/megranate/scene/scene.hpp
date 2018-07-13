//
//  scene.hpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef scene_hpp
#define scene_hpp

#include "camera.hpp"
#include "entity.hpp"
#include "pipeline.hpp"
#include <map>
namespace megranate {
    class Scene : public Object{
        MEGRANATE_OBJECT(Scene, Object);
        
    public:
        Scene(Context* context);
        ~Scene();
    public:
        mg_bool update();
        mg_void draw();
        mg_void touch_event();
        mg_void shutdown();
        mg_void keyboard();
    public:
        mg_bool load_res(const mg_char*);
        mg_bool insert_entity(Entity*);
        mg_bool insert_orth(Entity*);
    private:
        mg_void release();
        Entity* create_child(std::string name, CreateMode mode = REPLICATED, mg_uint id = 0, mg_bool temporary = false);
        
    private:
        Camera _camera;
        Pipeline _pipeline;
        std::map<StringHash, Entity*> _entities;
        Entity* _root = nullptr;
        Context* _context = nullptr;
        std::string _dir;
    };
}

#endif /* scene_hpp */
