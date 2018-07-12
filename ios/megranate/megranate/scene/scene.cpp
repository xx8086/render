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
    
    mg_void Scene::draw(){
        ;
    }
    
    mg_void Scene::touch_event(){
        ;
    }
    
    mg_void Scene::shutdown(){
        ;
    }
    
    mg_void Scene::keyboard(){
        ;
    }
    //
    
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
    
    Entity* Scene::create_child(std::string name, CreateMode mode, mg_uint id, mg_bool temporary){
        Entity* entity;
        return entity;
    }
    
    
    Entity* Scene::create_child(mg_uint id, CreateMode mode, mg_bool temporary){
        Entity* entity;
        return entity;
    }
    
    mg_void Scene::add_child(Entity* e, mg_uint index){
        ;
    }
    
    mg_bool Scene::load_res(const mg_char* res){
        return true;
    }
}
