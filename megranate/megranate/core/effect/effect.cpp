//
//  effect.cpp
//  megranate
//
//  Created by liu on 2018/7/17.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "effect.hpp"

namespace megranate {
     Effect::Effect(Context* context) : Component(context){
        _shader = new Shader(context);
    }
    
    Effect::~Effect(){
        release();
    }
    
    mg_void Effect::bind(){
        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &_vbo);
        glGenBuffers(1, &_ebo);
        
        glBindVertexArray(_vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(mg_float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(mg_float), (void*)(3 * sizeof(mg_float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(mg_float), (void*)(6 * sizeof(mg_float)));
        glEnableVertexAttribArray(2);
    }
    
    mg_bool Effect::load_res(const std::string& strdir){
        if (GL_FALSE == _shader->loadshader(strdir.c_str(),
                                            "effect_face.vs",
                                            "effect_face.fs")){
            return false;
        }
        
        std::string str_imge(strdir);
        str_imge.append("/niuyan.jpg");
        _materials.set_texture_size(1);
        _materials.push_texture(1, str_imge);
        bind();
        return true;
    }
    mg_void Effect::update(){
        if (_timer.count_time()){
            if (_ratio <= 0.2 || _ratio > 1.0){//0.45
                _step = -_step;
            }
            _ratio += _step;
            _timer.set_count_time(50);
        }
    }
    mg_void Effect::draw(const Mat4f &project, const Mat4f &view, const Mat4f &world){
        _shader->use();
        _shader->setfloat(_shader->getuniformlocation("ratio"), _ratio);
        _materials.render(0);
        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        _shader->unuse();
    }
    
    mg_void Effect::release(){
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
        
        if (nullptr != _shader){
            delete _shader;
            _shader = nullptr;
        }
    }
}
