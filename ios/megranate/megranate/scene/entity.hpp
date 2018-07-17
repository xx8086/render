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
#include "../math/quaternion.hpp"
#include "type_render.h"
#include "entity.hpp"
#include "context.h"
#include "pipeline.hpp"
#include "component.hpp"
#include <vector>

namespace megranate {
    class Component;
    class Camera;
    enum CreateMode{
        REPLICATED = 0,
        LOCAL = 1,
    };
    
    enum TransformSpace{
        TS_LOCAL = 0,
        TS_PARENT = 1,
        TS_WORLD = 2,
    };
    
    class Entity : public Object{
        MEGRANATE_OBJECT(Entity, Object);
    public:
        Entity(Context* context);

        mg_bool load_res(const std::string&);
        mg_bool draw(Camera& camera);
        mg_bool update();
        mg_void translate(const Vec3f&, TransformSpace);
        mg_void set_postion(const Vec3f&);
        mg_void set_rotation(const Vec3f&);
        mg_void set_scale(mg_float);
        mg_void set_scale(const Vec3f&);
        mg_void add_children(Entity* children);
    public:
        template<typename T>
        T* create_component(CreateMode mode = REPLICATED, mg_uint id = 0){
            StringHash type = T::get_type_static();
            Object* o = _context->create_object(type);
            Component* new_component = (Component*)(o);
            add_compoent(new_component);
            return dynamic_cast<T*>(new_component);
        }
    
        template <class T> mg_void remove_component() {
            remove_component(T::GetTypeStatic());
        }
        
        mg_bool is_visible() const{return _visible;}
        mg_void set_visible(mg_bool v){_visible = v;}
        Component* get_component(StringHash hash, mg_bool recursive = false) const;
        
    private:
        mg_void remove_component(StringHash type);
        mg_void add_compoent(Component*);
    private:
        mg_uint  _id;
        mg_bool _visible = false;
        Entity* _parent = nullptr;
        std::vector<Entity*> _children;
        std::vector<Component*> _components;
        Vec3f _rotation;
        Vec3f _postion;
        Vec3f _scale;
        //Quaternion _rotation;
        //mutable Quaternion _world_rotation;
        mutable Mat4f _world_transform;
        /*
         p.scale(0.1);
         p.rotate(270.0, 180.0, 0.0);
         p.world_pos(0.0f, -2.0f, 0.0f);
         */
        std::string _name;
        std::string _hash;
        Pipeline _pipeline;
        
    };
}

#endif /* entity_hpp */
