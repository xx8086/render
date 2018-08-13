//
//  framebuffer.hpp
//  megranate
//
//  Created by liu on 2018/8/13.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef framebuffer_hpp
#define framebuffer_hpp
#include "shader.hpp"

namespace megranate {
    class FrameBuffer : public Object{
        MEGRANATE_OBJECT(FrameBuffer, Object);
    public:
        FrameBuffer(Context* context);
        ~FrameBuffer();
    public:
        Shader* get_shader()const;
        mg_void bind_default_frame_buffer_id();
        mg_void bind_current_frame_buffer_id();
        mg_void bind_render_buffer_id();
        mg_void bind_texture_buffer_id(mg_uint texture_unit);
        mg_int get_default_frame_buffer_id();
    private:
        mg_void gen_quad();
        mg_void gen_texturebuffer();
        mg_void gen_renderbuffer();
        mg_void release();
    private:
        Shader* _framebuffer_shader = nullptr;
        mg_int _width = 0;
        mg_int _height = 0;
        mg_uint _render_buffer_id = 0;
        mg_uint _texture_buffer_id = 0;
        mg_uint _quad_vbo = 0;
        mg_uint _quad_vao = 0;
        mg_uint _current_id = 0;
        mg_int _default_id = 0;
    };
}
#endif /* framebuffer_hpp */
