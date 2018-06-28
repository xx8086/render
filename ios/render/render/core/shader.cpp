//
//  shader.cpp
//  lh_render
//
//  Created by liu on 2018/6/19.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "shader.hpp"
#include <stdlib.h>
#include <fstream>
#include <sstream>

CShader::CShader(){
    ;
}

CShader::~CShader(){
    ;
}

const GLuint& CShader::programid() const{
    return _program;
}

GLuint CShader::loadshader(GLenum type, const char *loadshader)
{
    GLuint shader = 0;
    GLint compiled = 0;
    shader = glCreateShader (type);
    if (0 == shader){
        return 0;
    }
    
    glShaderSource(shader, 1, &loadshader, NULL);
    glCompileShader(shader );
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled){
        GLint info_len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
        if ( info_len > 1 ){
            char *info_log = (char*)malloc(sizeof(char) * info_len);
            glGetShaderInfoLog (shader, info_len, NULL, info_log);
            esLogMessage ("Error compiling shader:\n%s\n", info_log);
            free (info_log);
        }
        
        glDeleteShader (shader);
        return 0;
    }
    
    return shader;
}

GLboolean CShader::loadshader(const char* vs, const char* fs){
//int Init ( ESContext *esContext ){
    //UserData *userData = (UserData*)esContext->userData;
    if (nullptr == vs  || nullptr == fs){
        return GL_FALSE;
    }
    
    GLuint vertex_shader = 0;
    GLuint fragment_shader = 0;
    GLuint program_object = 0;
    GLint linked = 0;
    
    vertex_shader = loadshader(GL_VERTEX_SHADER, vs);
    fragment_shader = loadshader(GL_FRAGMENT_SHADER, fs);
    program_object = glCreateProgram();
    if (0 == program_object){
        return 0;
    }
    
    glAttachShader(program_object, vertex_shader);
    glAttachShader(program_object, fragment_shader);
    glLinkProgram(program_object);
    glGetProgramiv(program_object, GL_LINK_STATUS, &linked);
    if (!linked){
        GLint info_len = 0;
        glGetProgramiv(program_object, GL_INFO_LOG_LENGTH, &info_len);
        if (info_len > 1){
            char *info_log = (char*)malloc( sizeof(char) * info_len);
            glGetProgramInfoLog (program_object, info_len, NULL, info_log);
            esLogMessage ("Error linking program:\n%s\n", info_log);
            free (info_log);
        }
        glDeleteProgram (program_object);
        return GL_FALSE;
    }
    
    _program = program_object;
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    return GL_TRUE;
}


GLboolean CShader::loadshader(const char*dir, const char* vs_file_name, const char* fs_file_name){
    if(nullptr == dir || nullptr == vs_file_name || nullptr == vs_file_name){
        return GL_FALSE;
    }
    std::string strvs(dir);
    std::string strfs(dir);
    strvs.append("/");
    strvs.append(vs_file_name);
    strfs.append("/");
    strfs.append(fs_file_name);
    std::string vs_content = loadfile(strvs.c_str());
    std::string fs_content = loadfile(strfs.c_str());
    return loadshader(vs_content.c_str(), fs_content.c_str());
}

std::string CShader::loadfile(const char* file){
    std::string strcontent;
    if(nullptr != file){
        std::ifstream t(file);
        if(t){
            std::stringstream buffer;
            buffer << t.rdbuf();
            strcontent = buffer.str();
            t.close();
        }
    }
    return strcontent;
}
// activate the shader
// ------------------------------------------------------------------------
void CShader::use(){
    glUseProgram(_program);
}

void CShader::setbool(GLint location, bool value) const{
    glUniform1i(location, (int)value);
}
void CShader::setint(GLint location, int value) const{
    glUniform1i(location, value);
}
void CShader::setfloat(GLint location, float value) const{
    glUniform1f(location, value);
}

void CShader::setvec2(GLint location, float x, float y) const{
    glUniform2f(location, x, y);
}

void CShader::setvec3(GLint location, float x, float y, float z) const{
    glUniform3f(location, x, y, z);
}
void CShader::setvec4(GLint location, float x, float y, float z, float w){
    glUniform4f(location, x, y, z, w);
}

void CShader::setmat4(GLint location, const Mat4f &mat, GLboolean transpose) const{
    glUniformMatrix4fv(location, 1, transpose, (const GLfloat*)mat);
}

int CShader::getuniformlocation(const char* name){
    return glGetUniformLocation(_program, name);
}


