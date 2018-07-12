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
#include <vector>

namespace megranate {
    class Component;
    
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
    public:
        mg_bool draw();
        mg_bool update();

    public:
        mg_void translate(const Vec3f&, TransformSpace);
        mg_void set_transform(float, const Vec3f&, const Quaternion&);
        mg_void set_transform(const Vec3f&, const Vec3f&, const Quaternion&);
        mg_void set_postion(const Vec3f&);
        mg_void set_scale(mg_float);
        mg_void set_scale(const Vec3f&);
        mg_void set_rotation(const Quaternion&);
        //void set_world_postion(const Vec3f&);
        //void set_world_scale(float);
        //void set_world_scale(const Vec3f&);
        //void set_world_rotation(const Quaternion&);
        
        Mat3x4f make_mat3x4(const Vec3f& translation, const Quaternion& rotation, const Vec3f& scale) const;
        Mat3x4f get_tarnsform() const;
        const Mat4f& get_world_tarnsform() const;
    public:
        template<typename T> T* create_component(CreateMode mode, mg_uint id){
            return static_cast<T*>(create_component(T::get_type_static(), mode, id));
        }
        

        template <class T> mg_void remove_component() {
            remove_component(T::GetTypeStatic());
        }
        
        mg_bool is_visible() const{return _visible;}
        mg_void set_visible(mg_bool v){_visible = v;}
        Component* get_component(StringHash hash, mg_bool recursive = false) const;
        
    private:
        mg_void remove_component(StringHash type);
        Component* create_component(StringHash type, CreateMode mode = REPLICATED, mg_uint id = 0);
        mg_void add_compoent(Component*);
    private:
        mg_uint  _id;
        mg_bool _visible = false;
        Entity* _parent = nullptr;
        std::vector<Entity*> _children;
        std::vector<Component*> _components;
        Vec3f _postion;
        Vec3f _scale;
        Quaternion _rotation;
        mutable Quaternion _world_rotation;
        mutable Mat4f _world_transform;
        std::string _name;
        std::string _hash;
        
    };
}

#endif /* entity_hpp */
