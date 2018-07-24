//
//  materials.hpp
//  megranate
//
//  Created by liu on 2018/7/16.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef materials_hpp
#define materials_hpp
#include "../object/texture.hpp"
#include <vector>

namespace megranate {
    class Materials{
    public:
        Materials();
        ~Materials();
    public:
        mg_bool push_texture(mg_uint index,  std::string& text_path);
        mg_void set_texture_size(mg_uint);
        mg_void render(mg_uint index);
        mg_void release();
    private:
        std::vector<TextureGl*> _textures;
    };
}

#endif /* materials_hpp */
