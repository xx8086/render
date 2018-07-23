//
//  interface_render.cpp
//  render
//
//  Created by liu on 2018/6/26.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "../../include/interface_render.hpp"
#include "single.h"
#include "scene.hpp"

namespace megranate {
    Scene* get_render(){
        return Singleton<Scene>::get_instance();
        //return Singleton<CBones>::get_instance();
        
    }
    
    CInterfaceRender::CInterfaceRender(){
        ;
    }
    
    CInterfaceRender::~CInterfaceRender(){
        ;
    }
    int CInterfaceRender::esMain(ESContext *esContext){
        esContext->scene = get_render();
        esCreateWindow(esContext, "CBones", esContext->width, esContext->height, ES_WINDOW_RGB);
        return esContext->scene->load_res(esContext);
    }
}
