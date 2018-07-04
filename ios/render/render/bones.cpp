//
//  bones.cpp
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "bones.hpp"
#include "pipeline.hpp"

CBones::CBones(){
}

CBones::~CBones(){
    release();
}

void CBones::init(){
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
    _camera->resize(w, h);
    glViewport (0, 0, _width, _height);
}

void CBones::draw(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _shader.use();

    std::vector<Mat4f> transform;
    _bones_mesh->bone_transform(_time.interval_ms()/1000.0f, transform);
    for (unsigned int i = 0 ; i < transform.size() ; i++) {
        _shader.set_bones_uniformlocation(i, transform[i]);
    }
    
    Pipeline p;
    p.set_camera(Vec3f(0.0f, 0.0f, -10.0f), Vec3f(0.0f, 0.0f, 1.0f), Vec3f(0.0f, 1.0f, 0.0f));
    p.set_perspective_proj(_camera->get_proj_info());
    p.scale(0.1);
    p.rotate(270.0, 180.0, 0.0);
    p.world_pos(0.0f, -2.5f, 0.0f);
    _shader.setmat4(_shader.getuniformlocation("pvw"), p.get_pvw_trans(), GL_TRUE);
    //_shader.setmat4(_shader.getuniformlocation("model"), p.get_world_trans());
    _bones_mesh->render();
    _shader.unuse();
}

void CBones::shutdown(){
    glDeleteProgram (_shader.programid());
}

int CBones::esMain (ESContext *esContext){
    esContext->render = (CRender*)this;
    _dir = esContext->appdir;
    esCreateWindow(esContext, "CBones", esContext->width, esContext->height, ES_WINDOW_RGB);
    if (GL_FALSE == _shader.loadshader(esContext->appdir,
                                       "skinning.vs",
                                       "skinning.fs")){
        return GL_FALSE;
    }
    
    std::string strmodel(esContext->appdir);
    strmodel.append("/boblampclean.md5mesh");
    //strmodel.append("/Hyperspace_Madness_Killamari_Minion2.fbx");
    init();
    _camera = new Camera(Vec3f(0.0f, 0.0f, -10.0f));
    _bones_mesh = new BonesMesh();
    _bones_mesh->load_mesh(strmodel);
    _shader.set_bones_counts(_bones_mesh->num_bones());
    _shader.bone_uniformlocation();
    _shader.setint(_shader.getuniformlocation("gColorMap"), 0);
    resize(esContext->width, esContext->height);
    PersProjInfo sp;
    sp.FOV = 60;
    sp.Width = esContext->width;
    sp.Height = esContext->height;
    sp.zNear = 0.1;
    sp.zFar = 100;
    _camera->set_proj_info(sp);
    
    return GL_TRUE;
}
