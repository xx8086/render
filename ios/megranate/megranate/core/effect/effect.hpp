//
//  effect.hpp
//  megranate
//
//  Created by liu on 2018/7/17.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef effect_hpp
#define effect_hpp

#include "shader.hpp"
#include "../../scene/component.hpp"
#include "../../render/materials.hpp"
#include "../../object/timer.hpp"

namespace megranate {
    class Effect : public Component {
        MEGRANATE_OBJECT(Effect, Object);
    public:
        Effect(Context* context);
        virtual ~Effect();
    public:
        virtual mg_bool load_res(const std::string&);
        virtual mg_void update();
        virtual mg_void draw(const Mat4f &project, const Mat4f &view, const Mat4f &world);
    private:
        mg_void release();
        mg_void bind();
    private:
        Shader* _shader = nullptr;
        Timer _timer;
        mg_float _step = 0.03f;
        mg_float _ratio = 1.0f;
        Materials _materials;
        mg_uint _vbo;
        mg_uint _vao;
        mg_uint _ebo;
        mg_float vertices[32] = {
            // positions          // colors           // texture coords
            1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
            1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
            -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f // top left
        };
        mg_uint indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
    };
}

#endif /* effect_hpp */
