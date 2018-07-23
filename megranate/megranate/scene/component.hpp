//
//  component.hpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef component_hpp
#define component_hpp
//#include "entity.hpp"
#include "../object/object.h"
#include "../object/type_render.h"
#include <string>
namespace megranate {
    class Entity;
    class Object;
    class Camera;
    class Component : public Object{
        MEGRANATE_OBJECT(Component, Object);
        
    public:
        Component(Context* context) : Object(context){};
        virtual ~Component(){};
        virtual mg_bool load_res(const std::string& dir){return false;};
        virtual mg_void draw(const Mat4f &project, const Mat4f &view, const Mat4f &world){};
        virtual mg_void shutdown() {};
        virtual mg_void touch_event() {};
        virtual mg_void update(){};
    public:
        Component* get_component(StringHash type) const;
        template <class T> T* get_component() const { return static_cast<T*>(GetComponent(T::get_type_static())); }
        //void GetComponents(Vector<Component*>& dest, StringHash type) const;
        //template <class T> void get_component(Vector<T*>& dest) const;
        
    public:
        Entity* get_entity()const{return _entity;}
    protected:
        Entity* _entity;
        
    };
}
#endif /* component_hpp */
