//
//  scene.cpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "scene.hpp"

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

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
        
        Pipeline p;
        p.set_camera(Vec3f(0.0f, 0.0f, -10.0f), Vec3f(0.0f, 0.0f, 1.0f), Vec3f(0.0f, 1.0f, 0.0f));
        p.set_perspective_proj(_camera.get_proj_info());
        p.scale(0.1);
        p.rotate(270.0, 180.0, 0.0);
        p.world_pos(0.0f, -2.5f, 0.0f);
        _root->draw(p.get_pvw_trans());
        
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
    }
    
    mg_bool Scene::load_res(ESContext *esContext){
        resize(esContext->width, esContext->height);
        PersProjInfo sp;
        sp.FOV = 60;
        sp.Width = esContext->width;
        sp.Height = esContext->height;
        sp.zNear = 0.1;
        sp.zFar = 100;
        _camera.set_proj_info(sp);
        
        Entity* entity = create_child("skeletal");
        entity->load(esContext->appdir);
        return true;
    }
}
