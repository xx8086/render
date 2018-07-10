//
//  texture.hpp
//  megranate
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

#include "type_render.h"
#include <string>
namespace megranate {
    struct Vertex {
        Vec3f Position;
        Vec3f Normal;
        Vec2f TexCoords;
        Vec3f Tangent;
        Vec3f Bitangent;
    };
    
    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };
    
    class TextureGl: protected Texture{
    public:
        void bind(unsigned int texture_unit);
        unsigned int load_texture(const std::string &filename, bool gamma = false);
    private:
        unsigned int _texture_id;
    };
}
#endif /* texture_hpp */
