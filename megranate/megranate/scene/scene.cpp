//
//  scene.cpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "scene.hpp"
#include "../object/gl_file.h"
#include "../core/skeletal.hpp"
#include "../core/fonts/font.h"
#include "../core/effect/effect.hpp"

namespace megranate {
    Scene::Scene(Context* context) :
    Object(context), _context(context){
        _entities.clear();
        _root = new Entity(context);
        _entities.emplace(StringHash("root"), _root);
    }
    
    Scene::~Scene(){
        release();
    }
    
    mg_void Scene::draw(){
        if (nullptr == _root){
            return ;
        }
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _root->draw(_camera);
        
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
    
    mg_void Scene::release(){
        for (std::map<StringHash, Entity*>::iterator iter = _entities.begin();
             iter != _entities.end(); iter++){
            if (nullptr != iter->second){
                delete iter->second;
                iter->second = nullptr;
            }
        }
        _entities.clear();
        _root = nullptr;
    }
    
    mg_bool Scene::update(){
        return _root->update();
    }
    
    Entity* Scene::create_child(std::string name, CreateMode mode, mg_uint id, mg_bool temporary){
        Entity* entity = new Entity(_context);
        _root->add_children(entity);
        _entities.emplace(StringHash(name), entity);
        return entity;
    }
    
    mg_void Scene::resize(mg_uint w, mg_uint h){
        _width = w;
        _height = h;
        _camera.resize(w, h);
        glViewport (0, 0, _width, _height);
        glEnable(GL_DEPTH_TEST);
    }
    
    mg_bool Scene::load_res(ESContext *esContext){
        resize(esContext->width, esContext->height);
        PersProjInfo sp;
        sp.FOV = 45;
        sp.Width = esContext->width;
        sp.Height = esContext->height;
        sp.zNear = 0.1;
        sp.zFar = 100;
        _camera.set_proj_info(sp);
        _camera.set_postion(Vec3f(0.0f, 0.0f, -10.0f));
#if 0
        Entity* entity_fonts = create_child("fonts");
        CFont* fonts = entity_fonts->create_component<CFont>();
        entity_fonts->load_res(esContext->appdir);
        entity_fonts->set_postion(Vec3f(-3.0f, 0.0f, 0.0f));
        entity_fonts->set_rotation(Vec3f(0.0f, 0.0f, 0.0f));
        entity_fonts->set_scale(fonts->get_scalae());
#endif
#if 0
        Entity* entity_skeletal = create_child("Skeletal");
        Skeletal* skeletal = entity_skeletal->create_component<Skeletal>();
        entity_skeletal->load_res(esContext->appdir);
        entity_skeletal->set_postion(Vec3f(0.0f, -3.3f, 0.0f));
        entity_skeletal->set_rotation(Vec3f(-90.0f, 180.0f, 0.0f));
        entity_skeletal->set_scale(0.1f);
#endif
#if 1
        Entity* entity_effect = create_child("Effect");
        Effect* effect = entity_effect->create_component<Effect>();
        entity_effect->load_res(esContext->appdir);
      //effect.hpp
#endif
        
        
        //Skeletal* skeletal = entity->create_component<Skeletal>();
        return true;
    }
}
