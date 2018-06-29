//
//  shader.hpp
//  lh_render
//
//  Created by liu on 2018/6/19.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <stdio.h>
#include "context.hpp"
#include "type_render.h"
#include <string>

class CShader{
public:
    CShader();
    ~CShader();
public:
    std::string loadfile(const char* file);
    GLboolean loadshader(const char* vs, const char* fs);
    GLboolean loadshader(const char*dir, const char* vs_file_name, const char* fs_file_name);
    const GLuint& programid() const;
    void use();
    void unuse();
    void setbool(GLint location, bool value) const;
    void setfloat(GLint location, float value) const;
    void setint(GLint location, int value) const;
    void setvec2(GLint location, float x, float y) const;
    void setvec3(GLint location, float x, float y, float z) const;
    void setvec4(GLint location, float x, float y, float z, float w);
    void setmat4(GLint location, const Mat4f &mat, GLboolean transpose = GL_FALSE) const;
    int getuniformlocation(const char* name);
private:
    GLuint loadshader(GLenum type, const char *shader_src);
private:
    GLuint _program = 0;
};


#endif /* shader_hpp */
