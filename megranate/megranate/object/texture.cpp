//
//  texture.cpp
//  megranate
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 hanliu. All rights reserved.
//
#include "texture.hpp"
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "gl_file.h"

namespace megranate {
    void TextureGl::bind(mg_uint texture_unit){
        glActiveTexture(texture_unit);
        glBindTexture(GL_TEXTURE_2D, _texture_id);
    }
    
    unsigned int TextureGl::load_texture(const std::string &filename, mg_bool gamma){
        //std::string filename = std::string(path);
        //filename = directory + '/' + filename;
        
        mg_uint texture_id;
        glGenTextures(1, &texture_id);
        
        mg_int width;
        mg_int height;
        mg_int nrComponents;
        mg_uchar *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (nullptr != data){
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;
            
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            stbi_image_free(data);
        }
        else{
            printf("Texture failed to load at path: %s\n", path.c_str());
        }
        
        _texture_id = texture_id;
        return texture_id;
    }
}
