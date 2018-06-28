//
//  gl_triangle.hpp
//  lh_render
//
//  Created by liu on 2018/6/19.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef gl_triangle_hpp
#define gl_triangle_hpp

#include <stdio.h>
#include "context.hpp"
#include "shader.hpp"
#include "rander.hpp"
#include "model.hpp"
#include "camera.hpp"

class CTriangle: public CRender{
public:
    CTriangle();
    ~CTriangle();
    int esMain(ESContext *esContext);
private:
    virtual void release();
    virtual void init();
    virtual void draw();
    virtual void update();
    virtual void shutdown();
    virtual void keyboard();
    virtual void touch_event();
    void resize(unsigned int w, unsigned int h);
private:
    Model* _model = nullptr;
    Camera* _camera = nullptr;
    CShader _shader;
};

#endif /* gl_triangle_hpp */
