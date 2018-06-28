//
//  gl_triangle.cpp
//  lh_render
//
//  Created by liu on 2018/6/19.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "gl_triangle.hpp"

CTriangle::CTriangle(){
}

CTriangle::~CTriangle(){
    release();
}

void CTriangle::init(){
    glViewport (0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST);
}

void CTriangle::update(){
    ;
}
void CTriangle::keyboard(){
    ;
}
void CTriangle::touch_event(){
    ;
}
void CTriangle::release(){
    if(nullptr != _model){
        delete _model;
        _model = nullptr;
    }
    if(nullptr != _camera){
        delete _camera;
        _camera = nullptr;
    }
}

void CTriangle::resize(unsigned int w, unsigned int h){
    _width = w;
    _height = h;
    _camera->resize(w, h, 0.1, 100);
}

void CTriangle::draw(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _shader.use();
    _shader.setmat4(_shader.getuniformlocation("projection"), _camera->get_projection());
    _shader.setmat4(_shader.getuniformlocation("view"), _camera->get_view_matrix());

    glm::mat4 model;
    static float angle = 0.0f;
    angle += 0.1f;
    model = glm::translate(model, glm::vec3(0.0f, -1.5f, -2.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
    _shader.setmat4(_shader.getuniformlocation("model"), Mat4f(model));
    _model->Draw(_shader.programid());
}

void CTriangle::shutdown(){
    glDeleteProgram (_shader.programid());
}

int CTriangle::esMain (ESContext *esContext){
    esContext->render = (CRender*)this;
    esCreateWindow(esContext, "Triangle", esContext->width, esContext->height, ES_WINDOW_RGB);
    if (GL_FALSE == _shader.loadshader(esContext->appdir,
                                       "triangle.vs",
                                       "triangle.fs")){
        return GL_FALSE;
    }
    _dir = esContext->appdir;
    std::string strmodel(esContext->appdir);
    strmodel.append("/nanosuit.obj");
    
    init();
    _camera = new Camera(Vec3f(0.0f, 0.0f, 3.0f));
    _model = new Model(strmodel.c_str());
    resize(esContext->width, esContext->height);
    return GL_TRUE;
}
