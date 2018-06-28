//
//  context.cpp
//  lh_render
//
//  Created by liu on 2018/6/20.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include <stdio.h>
#include "context.hpp"

#include <fstream>
#include <sstream>
#include <iosfwd>//input output stream forward

#ifdef ANDROID
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/asset_manager.h>
typedef AAsset esFile;
#else
typedef FILE esFile;
#endif

#ifdef __APPLE__
//#include "FileWrapper.h"
#endif


#define INVERTED_BIT            (1 << 5)

#ifndef __APPLE__
#pragma pack(push,x1)                            // Byte alignment (8-bit)
#pragma pack(1)
#endif

typedef struct
#ifdef __APPLE__
__attribute__ ( ( packed ) )
#endif
{
    unsigned char  IdSize,
    MapType,
    ImageType;
    unsigned short PaletteStart,
    PaletteSize;
    unsigned char  PaletteEntryDepth;
    unsigned short X,
    Y,
    Width,
    Height;
    unsigned char  ColorDepth,
    Descriptor;
    
} TGA_HEADER;

#ifndef __APPLE__
#pragma pack(pop,x1)
#endif

#ifndef __APPLE__

EGLint GetContextRenderableType ( EGLDisplay eglDisplay )
{
#ifdef EGL_KHR_create_context
    const char *extensions = eglQueryString ( eglDisplay, EGL_EXTENSIONS );
    
    // check whether EGL_KHR_create_context is in the extension string
    if ( extensions != NULL && strstr( extensions, "EGL_KHR_create_context" ) )
    {
        // extension is supported
        return EGL_OPENGL_ES3_BIT_KHR;
    }
#endif
    // extension is not supported
    return EGL_OPENGL_ES2_BIT;
}
#endif


GLboolean ESUTIL_API esCreateWindow ( ESContext *esContext, const char *title, GLint width, GLint height, GLuint flags )
{
#ifndef __APPLE__
    EGLConfig config;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    if ( esContext == NULL ){
        return GL_FALSE;
    }
    
#ifdef ANDROID
    // For Android, get the width/height from the window rather than what the
    // application requested.
    esContext->width = ANativeWindow_getWidth ( esContext->eglNativeWindow );
    esContext->height = ANativeWindow_getHeight ( esContext->eglNativeWindow );
#else
    esContext->width = width;
    esContext->height = height;
#endif
    
    if ( !WinCreate ( esContext, title ) )
    {
        return GL_FALSE;
    }
    
    esContext->eglDisplay = eglGetDisplay( esContext->eglNativeDisplay );
    if ( esContext->eglDisplay == EGL_NO_DISPLAY ){
        return GL_FALSE;
    }
    
    // Initialize EGL
    if ( !eglInitialize ( esContext->eglDisplay, &majorVersion, &minorVersion ) ){
        return GL_FALSE;
    }
    
    {
        EGLint numConfigs = 0;
        EGLint attribList[] =
        {
            EGL_RED_SIZE,       5,
            EGL_GREEN_SIZE,     6,
            EGL_BLUE_SIZE,      5,
            EGL_ALPHA_SIZE,     ( flags & ES_WINDOW_ALPHA ) ? 8 : EGL_DONT_CARE,
            EGL_DEPTH_SIZE,     ( flags & ES_WINDOW_DEPTH ) ? 8 : EGL_DONT_CARE,
            EGL_STENCIL_SIZE,   ( flags & ES_WINDOW_STENCIL ) ? 8 : EGL_DONT_CARE,
            EGL_SAMPLE_BUFFERS, ( flags & ES_WINDOW_MULTISAMPLE ) ? 1 : 0,
            // if EGL_KHR_create_context extension is supported, then we will use
            // EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT in the attribute list
            EGL_RENDERABLE_TYPE, GetContextRenderableType ( esContext->eglDisplay ),
            EGL_NONE
        };
        
        // Choose config
        if ( !eglChooseConfig ( esContext->eglDisplay, attribList, &config, 1, &numConfigs ) ){
            return GL_FALSE;
        }
        
        if ( numConfigs < 1 ){
            return GL_FALSE;
        }
    }
    
    
#ifdef ANDROID
    // For Android, need to get the EGL_NATIVE_VISUAL_ID and set it using ANativeWindow_setBuffersGeometry
    {
        EGLint format = 0;
        eglGetConfigAttrib ( esContext->eglDisplay, config, EGL_NATIVE_VISUAL_ID, &format );
        ANativeWindow_setBuffersGeometry ( esContext->eglNativeWindow, 0, 0, format );
    }
#endif // ANDROID
    
    // Create a surface
    esContext->eglSurface = eglCreateWindowSurface(esContext->eglDisplay, config,
                                                   esContext->eglNativeWindow, NULL);
    
    if ( esContext->eglSurface == EGL_NO_SURFACE ){
        return GL_FALSE;
    }
    
    // Create a GL context
    esContext->eglContext = eglCreateContext(esContext->eglDisplay, config,
                                             EGL_NO_CONTEXT, contextAttribs);
    
    if ( esContext->eglContext == EGL_NO_CONTEXT ){
        return GL_FALSE;
    }
    
    // Make the context current
    if ( !eglMakeCurrent(esContext->eglDisplay, esContext->eglSurface,
                         esContext->eglSurface, esContext->eglContext))
    {
        return GL_FALSE;
    }
    
#endif // #ifndef __APPLE__
    
    return GL_TRUE;
}

void ESUTIL_API esLogMessage ( const char *formatStr, ... ){
    va_list params;
    char buf[BUFSIZ];
    
    va_start ( params, formatStr );
    vsprintf ( buf, formatStr, params );
    
#ifdef ANDROID
    __android_log_print ( ANDROID_LOG_INFO, "esUtil" , "%s", buf );
#else
    printf ( "%s", buf );
#endif
    
    va_end ( params );
}

const char* loadfile(const char* file){
#ifdef __APPLE__
    //file = GetBundleFileName (file);
#endif
    std::ifstream t(file);
    std::stringstream  sb;
    sb << t.rdbuf();
    std::string str(sb.str());
    return str.c_str();
}

void ESContext::draw(){
    if (nullptr != render){
        render->draw();
    };
}
void ESContext::shutdown(){
    if (nullptr != render){
        render->shutdown();
    };
}
void ESContext::keyboard(){
    if (nullptr != render){
        render->keyboard();
    };
}
void ESContext::touch_event(){
    if (nullptr != render){
        render->touch_event();
    };
}

void ESContext::update(){
    if (nullptr != render){
        render->update();
    };
}
