//
//  rander.hpp
//  lh_render
//
//  Created by liu on 2018/6/21.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef rander_hpp
#define rander_hpp

#include <stdio.h>
#include <string>

class CRender{
public:
    CRender();
    virtual ~CRender();
public:
    virtual void release() = 0;
    virtual void init() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void shutdown() = 0;
    virtual void keyboard() = 0;
    virtual void touch_event() = 0;
    
    std::string get_dir()const;
    std::string loadfile(const char* file);
protected:
    unsigned int get_width()const;
    unsigned int get_height()const;
protected:
    unsigned int _width = 0;
    unsigned int _height = 0;
    std::string _dir;
};


#endif /* rander_hpp */
