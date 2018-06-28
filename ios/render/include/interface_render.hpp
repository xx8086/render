//
//  interface_render.hpp
//  render
//
//  Created by liu on 2018/6/26.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef interface_render_hpp
#define interface_render_hpp

#include <stdio.h>
#include "context.hpp"

class CInterfaceRender{
public:
    CInterfaceRender();
    ~CInterfaceRender();
public:
    int esMain(ESContext *esContext);
};

#endif /* interface_render_hpp */
