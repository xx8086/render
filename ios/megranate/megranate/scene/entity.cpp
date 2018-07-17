//
//  entity.cpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "entity.hpp"
#include "../math/math_common.hpp"
#include "camera.hpp"
#include <assert.h>

namespace megranate {
    Entity::Entity(Context* context) :
    Object(context){
        ;
    }
    
    mg_bool Entity::draw(Camera& camera){
        _pipeline.set_camera(Vec3f(0.0f, 0.0f, -10.0f), Vec3f(0.0f, 0.0f, 1.0f), Vec3f(0.0f, 1.0f, 0.0f));
        _pipeline.set_perspective_proj(camera.get_proj_info());
        _pipeline.scale(_scale);
        _pipeline.rotate(_rotation);
        _pipeline.world_pos(_postion);
        _pipeline.set_proj_trans();
        _pipeline.set_view_trans();
        _pipeline.set_world_trans();
        for(auto iter_comp = _components.begin();
            iter_comp != _components.end();
            iter_comp++){
            (*iter_comp)->draw(_pipeline.get_proj_trans(), _pipeline.get_view_trans(), _pipeline.get_world_trans());
        }
        
        for(auto iter_entity = _children.begin();
            iter_entity != _children.end();
            iter_entity++){
            (*iter_entity)->draw(camera);
        }
        
        return true;
    }
    
    mg_bool Entity::update(){
        size_t children_size = _children.size();
        for(mg_int i = 0; i < children_size; i++){
            assert(nullptr != _children[i]);
            _children[i]->update();
        }
        
        return true;
    }
    
    mg_void Entity::set_postion(const Vec3f& pos){
        _postion = pos;
    }
    
    mg_void Entity::set_rotation(const Vec3f& rotation){
        _rotation = rotation;
    }
    
    mg_void Entity::set_scale(float scale){
        set_scale(Vec3f(scale, scale, scale));
    }
    mg_void Entity::set_scale(const Vec3f& scale){
        _scale = scale;
    }
    
    Component* Entity::get_component(StringHash hash, mg_bool recursive)const{
        std::vector<Entity*> _children;
        std::vector<Component*> _components;
        Component* comp = nullptr;
        for (std::vector<Component*>::iterator iter = _components.begin();
            iter != _components.end();
            iter++){
            if ((*iter)->get_type() == hash)
            {
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
    
    mg_void Entity::remove_component(StringHash type){
        for (auto iter = _components.begin();
            iter != _components.end();
            iter++){
            if ((*iter)->get_type() == type)
            {
                _components.erase(iter);
                break;
            }
        }
    }
    
    void Entity::add_compoent(Component* comp){
        _components.emplace_back(comp);
    }
    
    mg_bool Entity::load_res(const std::string& dir){
        for(auto iter_comp = _components.begin();
            iter_comp != _components.end();
            iter_comp++){
            (*iter_comp)->load_res(dir);
        }
        return true;
    }
    
    mg_void Entity::add_children(Entity* children){
        assert(nullptr != children);
        _children.emplace_back(children);
    }
}
