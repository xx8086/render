//
//  component.hpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef component_hpp
#define component_hpp
#include "entity.hpp"

namespace megranate {
    class Entity;
    
    class Component : public Object{
        MEGRANATE_OBJECT(Component, Object);
        
    public:
        Component(Context* context);
        virtual ~Component();
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
