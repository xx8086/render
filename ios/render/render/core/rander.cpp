//
//  rander.cpp
//  lh_render
//
//  Created by liu on 2018/6/21.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "rander.hpp"

CRender::CRender(){
    ;
}

CRender::~CRender(){
    ;
}

unsigned int CRender::get_width()const{
    return _width;
}

unsigned int CRender::get_height()const{
    return _height;
}

std::string CRender::get_dir()const{
    return _dir;
}

