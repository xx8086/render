//
//  materials.cpp
//  megranate
//
//  Created by liu on 2018/7/16.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "materials.hpp"
#include "../object/config_render.h"
#include "../object/gl_file.h"

namespace megranate {
    Materials::Materials(){
        ;
    }
    
    Materials::~Materials(){
        release();
    }
    
    mg_void Materials::render(mg_uint index){
        assert(index < _textures.size());
        if (_textures[index]) {
            _textures[index]->bind(GL_TEXTURE0);
        }
    }
    
    mg_void Materials::release(){
        for (mg_uint i = 0 ; i < _textures.size() ; i++) {
            SAFE_DELETE(_textures[i]);
            
        }
        _textures.clear();
    }
    
    mg_void Materials::set_texture_size(mg_uint size){
        _textures.resize(size);
    }
    
    mg_bool Materials::push_texture(mg_uint index, std::string& text_path){
        _textures[index] = new TextureGl();
        if (!_textures[index]->load_texture(text_path)) {
            printf("Error loading texture '%s'\n", text_path.c_str());
            delete _textures[index];
            _textures[index] = NULL;
            return false;
        }
        else {
            printf("%d - loaded texture '%s'\n", index, text_path.c_str());
        }
        
        return true;
    }
}
    
