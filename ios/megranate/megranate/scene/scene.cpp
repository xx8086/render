//
//  scene.cpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "scene.hpp"
namespace megranate {
    Scene::Scene(Context* context) :
    Object(context){
        ;
    }
    
    Scene::~Scene(){
        release();
    }
    
    mg_void Scene::release(){
        for (std::map<StringHash, Entity*>::iterator iter = _entities.begin();
             iter != _entities.end(); iter++){
            if (nullptr != iter->second){
                delete iter->second;
                iter->second = nullptr;
            }
        }
        _entities.clear();
    }
    
    mg_bool Scene::update(){
        return _root->update();
    }
    
    Entity* Scene::create_child(std::string name, CreateMode mode, unsigned int id, bool temporary){
        Entity* entity;
        return entity;
    }
    
    
    Entity* Scene::create_child(unsigned id, CreateMode mode, bool temporary){
        Entity* entity;
        return entity;
    }
    
    mg_void add_child(Entity* e, unsigned int index){
        ;
    }
}
