//
//  gl_file.h
//  megranate
//
//  Created by liu on 2018/8/13.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef gl_file_h
#define gl_file_h

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
//#include <OpenGLES/ES3/glext.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

#endif /* gl_file_h */
