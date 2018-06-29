//
//  gl_triangle.cpp
//  lh_render
//
//  Created by liu on 2018/6/19.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "gl_triangle.hpp"
#include "pipeline.hpp"

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
    _camera->resize(w, h);
}

void CTriangle::draw(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _shader.use();
    static float angle = 0.0f;
    angle += 1.0f;
    Pipeline p;
    p.set_camera(_camera->get_postion(), _camera->get_target(), _camera->get_up());
    p.set_perspective_proj(_camera->get_proj_info());
    p.scale(0.1);
    p.rotate(angle, 0, 0);
    p.world_pos(0.0f, 0.0f, 6.0f);
    _shader.setmat4(_shader.getuniformlocation("wvp"), p.get_wvp_trans());
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
    
    _camera = new Camera(Vec3f(0.0f, 3.0f, -1.0f));
    _model = new Model(strmodel.c_str());
    init();
    resize(esContext->width, esContext->height);
    PersProjInfo sp;
    sp.FOV = 60;
    sp.Width = esContext->width;
    sp.Height = esContext->height;
    sp.zFar = 100;
    sp.zNear = 0.1;
    _camera->set_proj_info(sp);
    return GL_TRUE;
}
