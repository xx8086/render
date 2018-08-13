//
//  framebuffer.cpp
//  megranate
//
//  Created by liu on 2018/8/13.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "framebuffer.hpp"
#include "../object/gl_file.h"
#include "../object/log.hpp"

namespace megranate {
    
    mg_float _quad_vertices[] = {
        -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f, 0.0f,
        1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        
        -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,
        1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        1.0f,  1.0f,  0.0f, 1.0f, 1.0f};

    //FrameBuffer(Context* context);
    FrameBuffer::FrameBuffer(Context* context) : Object(context){
        _framebuffer_shader = new Shader(context);
    }
    
    FrameBuffer::~FrameBuffer(){
        release();
    }
    mg_void FrameBuffer::gen_quad(){
        glGenVertexArrays(1, &_quad_vao);
        glGenBuffers(1, &_quad_vbo);
        glBindVertexArray(_quad_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _quad_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_quad_vertices), &_quad_vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(5 * sizeof(float)));
        glBindVertexArray(0);
    }
    
    
    mg_void FrameBuffer::gen_renderbuffer(){
        get_default_frame_buffer_id();
        if (0 == _current_id)glGenFramebuffers(1, &_current_id);
        glBindFramebuffer(GL_FRAMEBUFFER, _current_id);
        
        glGenRenderbuffers(1, &_render_buffer_id);
        glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer_id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _render_buffer_id);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            log_printf("ERROR::FRAMEBUFFER:: GL_RENDERBUFFER is not complete!");
        }
        bind_default_frame_buffer_id();
        
    }
    mg_void FrameBuffer::gen_texturebuffer(){
        get_default_frame_buffer_id();
        if (0 == _current_id)glGenFramebuffers(1, &_current_id);
        glBindFramebuffer(GL_FRAMEBUFFER, _current_id);
        
        glGenTextures(1, &_texture_buffer_id);
        glBindTexture(GL_TEXTURE_2D, _texture_buffer_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture_buffer_id, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            log_printf("ERROR::FRAMEBUFFER:: GL_TEXTURE_2D is not complete!");
        }
        bind_default_frame_buffer_id();
    }
    
    mg_void FrameBuffer::release(){
        if (0 != _texture_buffer_id)glDeleteTextures(1, &_texture_buffer_id);
        if (0 != _render_buffer_id)glDeleteRenderbuffers(1, &_render_buffer_id);
        if (0 != _current_id)glDeleteFramebuffers(1, &_current_id);
        if (nullptr != _framebuffer_shader){
            delete _framebuffer_shader;
            _framebuffer_shader = nullptr;
        }
    }
    
    mg_int FrameBuffer::get_default_frame_buffer_id(){
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_default_id);
        return _default_id;
    }
    mg_void FrameBuffer::bind_default_frame_buffer_id(){
        glBindFramebuffer(GL_FRAMEBUFFER, _default_id);
    }
    mg_void FrameBuffer::bind_current_frame_buffer_id(){
        glBindFramebuffer(GL_FRAMEBUFFER, _current_id);
    }
    mg_void FrameBuffer::bind_render_buffer_id(){
        glBindTexture(GL_TEXTURE_2D, _texture_buffer_id);
    }
    mg_void FrameBuffer::bind_texture_buffer_id(mg_uint texture_unit){
        glActiveTexture(texture_unit);
        glBindTexture(GL_TEXTURE_2D, _texture_buffer_id);
    }
    Shader* FrameBuffer::get_shader()const{
        return _framebuffer_shader;
    }
}
