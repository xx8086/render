//
//  shader.hpp
//  megranate
//
//  Created by liu on 2018/7/12.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include "../object/context.h"
#include "../object/type_render.h"
#include "../object/gl_file.h"

namespace megranate {
    class Shader : public Object{
        MEGRANATE_OBJECT(Shader, Object);
    public:
        Shader(Context* context);
        ~Shader();
    public:
        std::string loadfile(const mg_char* file);
        GLboolean loadshader(const mg_char* vs, const mg_char* fs);
        GLboolean loadshader(const mg_char* dir, const mg_char* vs_file_name, const mg_char* fs_file_name);
        const GLuint& programid() const;
        mg_int getuniformlocation(const mg_char* name);
        mg_void use();
        mg_void unuse();
        mg_void setbool(GLint location, mg_bool value) const;
        mg_void setfloat(GLint location, mg_float value) const;
        mg_void setint(GLint location, mg_int value) const;
        mg_void setvec2(GLint location, mg_float x, mg_float y) const;
        mg_void setvec3(GLint location, mg_float x, mg_float y, mg_float z) const;
        mg_void setvec4(GLint location, mg_float x, mg_float y, mg_float z, mg_float w);
        mg_void setmat4(GLint location, const Mat4f &mat, GLboolean transpose = GL_FALSE) const;
        mg_void set_attrib_location(const mg_char *name, mg_int i);
    private:
        GLuint loadshader(GLenum type, const mg_char *shader_src);
    private:
        GLuint _program = 0;
    };
}


#endif /* shader_hpp */
