//
//  entity.cpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "entity.hpp"
#include "component.hpp"
#include "../math/math_common.hpp"
#include <assert.h>

namespace megranate {
    Entity::Entity(Context* context) :
    Object(context){
        ;
    }
    
    mg_bool Entity::draw(){
        
        return true;
    }
    
    mg_bool Entity::update(){
        size_t children_size = _children.size();
        for(int i = 0; i < children_size; i++){
            assert(nullptr != _children[i]);
            _children[i]->update();
        }
        
        draw();
        return true;
    }
    
    void Entity::set_transform(float scale, const Vec3f& position, const Quaternion& rotation){
        _scale = Vec3f(scale, scale, scale);
        _postion = position;
        _rotation = rotation;
    }
    
    void Entity::set_transform(const Vec3f& scale, const Vec3f& position, const Quaternion& rotation){
        _scale = scale;
        _postion = position;
        _rotation = rotation;
    }
    
    void Entity::set_postion(const Vec3f& pos){
        _postion = pos;
    }
    void Entity::set_scale(float scale){
        set_scale(Vec3f(scale, scale, scale));
    }
    void Entity::set_scale(const Vec3f& scale){
        _scale = scale;
    }
    void Entity::set_rotation(const Quaternion& rotaion){
        _rotation = rotaion;
    }
    
    const Mat4f& Entity::get_world_tarnsform() const{
        return _world_transform;
    }
    
    Mat3x4f Entity::make_mat3x4(const Vec3f& translation, const Quaternion& rotation, const Vec3f& scale) const{
        Mat3f m3f = rotation.rotation_matrix();
        m3f.sacled(scale);
        Mat3x4f mf = Mat3to3_4(m3f);
        Vec4f v4f(translation.x, translation.y, translation.z, 1.0f);
        mf.set_translation(v4f);
        return mf;
    }
    
    Mat3x4f Entity::get_tarnsform() const{
        return make_mat3x4(_postion, _rotation, _scale);
    }
    
    void Entity::translate(const Vec3f& delta, TransformSpace space){
        switch(space){
            case TS_LOCAL:
                _postion += _rotation * delta;
                break;
            case TS_PARENT:
                break;
            case TS_WORLD:
                break;
        }
    }
    
    Component* Entity::get_component(StringHash hash, bool recursive)const{
        std::vector<Entity*> _children;
        std::vector<Component*> _components;
        Component* comp = nullptr;
        for (std::vector<Component*>::iterator iter = _components.begin();
            iter != _components.end();
            iter++){
            if ((*iter)->get_type() == hash){
                comp = *iter ;
                break;
            }
        }
        
        if(nullptr == comp && recursive){
            for (std::vector<Entity*>::iterator iter = _children.begin();
                iter != _children.end();
                iter++){
                comp = (*iter)->get_component(hash, true);
                if(nullptr != comp){
                    break;
                }
            }
        }
        return comp;
    }
    
    void Entity::remove_component(StringHash type){
        for (auto iter = _components.begin();
            iter != _components.end();
            iter++){
            if ((*iter)->get_type() == type){
                _components.erase(iter);
                break;
            }
        }
    }
    
    Component* Entity::create_component(StringHash type, CreateMode mode, unsigned int id){
        if (id > FIRST_LOCAL_ID && mode == REPLICATED){
            id = LOCAL;
        }
        
        Component* new_component = dynamic_cast<Component*>(_context->create_object(type));
        add_compoent(new_component);
        return new_component;
    }
    
    void Entity::add_compoent(Component* comp){
        _components.emplace_back(comp);
    }
    
    
}
