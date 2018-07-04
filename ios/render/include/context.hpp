//
//  context.hpp
//  lh_render
//
//  Created by liu on 2018/6/19.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef context_hpp
#define context_hpp

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

#include "rander.hpp"

#ifdef WIN32
#define ESUTIL_API  __cdecl
#define ESCALLBACK  __cdecl
#else
#define ESUTIL_API
#define ESCALLBACK
#endif
    
#define ES_WINDOW_RGB           0
#define ES_WINDOW_ALPHA         1
#define ES_WINDOW_DEPTH         2
#define ES_WINDOW_STENCIL       4
#define ES_WINDOW_MULTISAMPLE   8
    
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
    
    typedef struct ESContext ESContext;
    struct ESContext{
        void *platformData;
        //void *userData;
        const char* appdir;
        const char* srcfile;
        CRender* render = nullptr;
        GLint width;
        GLint height;
#ifndef __APPLE__
        EGLNativeDisplayType eglNativeDisplay;
        EGLNativeWindowType eglNativeWindow;
        EGLDisplay eglDisplay;
        EGLContext eglContext;
        EGLSurface eglSurface;
#endif
        
        void draw();
        void shutdown();
        void keyboard();
        void touch_event();
        void update();
    };

GLboolean ESUTIL_API esCreateWindow(ESContext *esContext, const char *title, GLint width, GLint height, GLuint flags);
void ESUTIL_API esRegisterDrawFunc(ESContext *esContext,
                                   void(ESCALLBACK *drawFunc)(ESContext *));
void ESUTIL_API esRegisterShutdownFunc(ESContext *esContext,
                                       void(ESCALLBACK *shutdownFunc)(ESContext *));
void ESUTIL_API esRegisterUpdateFunc(ESContext *esContext,
                                     void(ESCALLBACK *updateFunc)(ESContext *, float));
void ESUTIL_API esRegisterKeyFunc(ESContext *esContext,
                                  void(ESCALLBACK *drawFunc)(ESContext *, unsigned char, int, int));
void ESUTIL_API esLogMessage(const char *formatStr, ...);
const char* loadfile(const char* file);

#endif /* context_h */
