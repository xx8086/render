//
//  texture.hpp
//  megranate
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp
#include "base_type.h"
#include "type_render.h"
#include <string>
namespace megranate {
    struct Vertex {
        Vec3f position;
        Vec3f normal;
        Vec2f tex_coords;
        Vec3f tangent;
        Vec3f bitangent;
    };
    
    struct Texture {
        mg_uint id;
        std::string type;
        std::string path;
    };
    
    class TextureGl: protected Texture{
    public:
        mg_void bind(mg_uint texture_unit);
        mg_uint load_texture(const std::string &filename, mg_bool gamma = false);
    private:
        mg_uint _texture_id;
    };
}
#endif /* texture_hpp */
