//
//  font.cpp
//  engine
//
//  Created by Liu,Han on 2017/9/1.
//

#include "font.h"
//#include "../render/render_system.h"
//#include "../utils/glutils.h"
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

namespace megranate{
    CFont::CFont(Context* context): Component(context){
        _fontshader_side = new Shader(context);
        _fontshader_deep = new Shader(context);
        _fontshader = new Shader(context);
    };
    
    void CFont::set_ttf(std::string _ttf){
        _str_fontttf = _ttf;
    }
    
    void CFont::draw(const Mat4f &proj, const Mat4f &view, const Mat4f &model){
        glUseProgram(0);
        //glEnable(GL_DEPTH_TEST);
        //glDisable(GL_CULL_FACE);
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#if 1
        _fontshader_side->use();
        _fontshader_side->setmat4(_fontshader_side->getuniformlocation("proj"), proj, GL_TRUE);
        _fontshader_side->setmat4(_fontshader_side->getuniformlocation("view"), view, GL_TRUE);
        _fontshader_side->setmat4(_fontshader_side->getuniformlocation("model"), model, GL_TRUE);
        //_fontshader_side->set_attrib_location("vertex", 0);
        _fontshader_side->setvec3(_fontshader_side->getuniformlocation("textColor"), 1.0, 0.0, 0.0);
        _c3dfont.font_rend(CHARACTE_SIDE);
        glUseProgram(0);
#endif
#if 1
        _fontshader_deep->use();
        _fontshader_deep->setmat4(_fontshader_deep->getuniformlocation("proj"), proj, GL_TRUE);
        _fontshader_deep->setmat4(_fontshader_deep->getuniformlocation("view"), view, GL_TRUE);
        _fontshader_deep->setmat4(_fontshader_deep->getuniformlocation("model"), model, GL_TRUE);
        //_fontshader_deep->set_attrib_location("vertex", 0);
        _fontshader_deep->setvec3(_fontshader_deep->getuniformlocation("textColor"), 9.0, 0.7, 0.0);
        _c3dfont.font_rend(CHARACTE_BACK);
        glUseProgram(0);
#endif
#if 1
        _fontshader->use();
        _fontshader->setmat4(_fontshader->getuniformlocation("proj"), proj, GL_TRUE);
        _fontshader->setmat4(_fontshader->getuniformlocation("view"), view, GL_TRUE);
        _fontshader->setmat4(_fontshader->getuniformlocation("model"), model, GL_TRUE);
        //_fontshader->set_attrib_location("vertex", 0);
        _fontshader->setvec3(_fontshader->getuniformlocation("textColor"), 0.7, 007, 0.0);
        _c3dfont.font_rend(CHARACTE_FRONT);
        glUseProgram(0);
#endif
    }
    void CFont::shader3dfont(){
        _c3dfont.set_fontfile(_str_fontttf.c_str());
        _scalae *= _c3dfont.get_sizeface_scalae(1.0);
        _c3dfont.set_depth(800.0);
        _c3dfont.set_outset(1.0, 1.0);
        _c3dfont.load_freetype();
        _c3dfont.insert_words((wchar_t*)_wstr_content.c_str(), _wstr_content.size());
    }
    
    mg_bool CFont::load_res(const std::string& strdir){
        if (GL_FALSE == _fontshader->loadshader(strdir.c_str(),
                                                "fonts.vs",
                                                "fonts.fs")){
            return false;
        }
        if (GL_FALSE == _fontshader_deep->loadshader(strdir.c_str(),
                                                     "fonts.vs",
                                                     "fonts.fs")){
            return false;
        }
        if (GL_FALSE == _fontshader_side->loadshader(strdir.c_str(),
                                                     "fonts.vs",
                                                     "fonts.fs")){
            return false;
        }
        
        std::string strttr(strdir);
        strttr.append("/hz.ttc");
        _str_fontttf = strttr;
        shader3dfont();
        return true;
    }
    
}
