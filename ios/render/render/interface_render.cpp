//
//  interface_render.cpp
//  render
//
//  Created by liu on 2018/6/26.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "interface_render.hpp"
#include "single.hpp"
#include "gl_triangle.hpp"
#include "bones.hpp"

CTriangle* get_render(){
    return Singleton<CTriangle>::get_instance();
    //return Singleton<CBones>::get_instance();
}

CInterfaceRender::CInterfaceRender(){
    ;
}

CInterfaceRender::~CInterfaceRender(){
    ;
}
int CInterfaceRender::esMain(ESContext *esContext){
    return get_render()->esMain(esContext);
}

