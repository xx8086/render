//
//  font.hpp
//  engine
//
//  Created by Liu,Han on 2017/9/1.
//

#ifndef font_hpp
#define font_hpp

#include "basefont.h"
#include "./3dfontskit/ftgenerate_tri.h"
#include "shader.hpp"
#include "../../scene/component.hpp"
#include <string>

namespace megranate{
    class CFont : public Component {
        MEGRANATE_OBJECT(CFont, Object);
    public:
        CFont(Context* context);
        virtual ~CFont() {};
        virtual mg_bool load_res(const std::string&);
        virtual mg_void draw(const Mat4f&, const Mat4f&, const Mat4f&);
        void set_ttf(std::string _ttf);
        mg_float get_scalae() const {return _scalae;};
    private:
        void shader3dfont();
    private: 
        std::string _str_fontttf;
        std::wstring _wstr_content = L"abc3@烤&串";
        float _anglex = 30.0f;
        float _angley = 20.0f;
        Shader* _fontshader;
        Shader* _fontshader_deep;
        Shader* _fontshader_side;
        CUseFont _cfont;
        
    private:
        CGenerateTri _c3dfont;
        mg_float _scalae = 1.0;
    };
}

#endif /* font_hpp */
