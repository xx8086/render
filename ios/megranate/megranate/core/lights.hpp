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
    class Lights : public Object{
        MEGRANATE_OBJECT(Lights, Object);
    public:
        Lights(Context* context);
    };
}

#endif /* lights_hpp */
