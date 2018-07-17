//
//  lights.hpp
//  megranate
//
//  Created by liu on 2018/7/11.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef lights_hpp
#define lights_hpp
#include "component.hpp"

namespace megranate {
    class Lights : public Component{
        MEGRANATE_OBJECT(Lights, Object);
    public:
        Lights(Context* context);
        //mg_void draw(const Mat4f &project, const Mat4f &view, const Mat4f &world){};
        //mg_bool load_res(const std::string&){return true;};
    };
}

#endif /* lights_hpp */
