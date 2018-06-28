//
//  bones.cpp
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "bones.hpp"
#include "timer.hpp"

CBones::CBones(){
}

CBones::~CBones(){
    release();
}

void CBones::init(){
    glViewport (0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST);
}

void CBones::update(){
    ;
}
void CBones::keyboard(){
    ;
}
void CBones::touch_event(){
    ;
}
void CBones::release(){
    if(nullptr != _bones_mesh){
        delete _bones_mesh;
        _bones_mesh = nullptr;
    }
    if(nullptr != _camera){
        delete _camera;
        _camera = nullptr;
    }
}

void CBones::resize(unsigned int w, unsigned int h){
    _width = w;
    _height = h;
    _camera->resize(w, h, 0.1, 100);
}

void CBones::draw(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _shader.use();

    std::vector<Mat4f> transform;
    static Timer seconds;
    _bones_mesh->bone_transform(seconds.interval_ms(), transform);
    seconds.set_count_time(0);
    for (unsigned int i = 0 ; i < transform.size() ; i++) {
        _shader.set_bones_uniformlocation(i, transform[i]);
    }
    
    _shader.setmat4(_shader.getuniformlocation("projection"), _camera->get_projection());
    _shader.setmat4(_shader.getuniformlocation("view"), _camera->get_view_matrix());
    
    glm::mat4 model;
    static float angle = 8.0f;
    //angle += 0.05f;
    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
    
    _shader.setmat4(_shader.getuniformlocation("model"), Mat4f(model));
    _bones_mesh->render();
}

void CBones::shutdown(){
    glDeleteProgram (_shader.programid());
}

int CBones::esMain (ESContext *esContext){
    esContext->render = (CRender*)this;
    _dir = esContext->appdir;
    esCreateWindow(esContext, "CBones", esContext->width, esContext->height, ES_WINDOW_RGB);
    if (GL_FALSE == _shader.loadshader(esContext->appdir,
                                       "skinning.fs",
                                       "skinning.fs")){
        return GL_FALSE;
    }
    
    std::string strmodel(esContext->appdir);
    strmodel.append("/oblampclean.md5mesh");
    
    init();
    _camera = new Camera(Vec3f(0.0f, 0.0f, 3.0f));
    _bones_mesh = new BonesMesh();
    _bones_mesh->loadmesh(strmodel.c_str());
    _shader.set_bones_counts(_bones_mesh->num_bones());
    _shader.bone_uniformlocation();
    _shader.setint(_shader.getuniformlocation("gColorMap"), 0);
    resize(esContext->width, esContext->height);
    return GL_TRUE;
}
